using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using HeaderCollector.Model;
using System.IO;
using System.Diagnostics;

namespace HeaderCollector
{
    public partial class MainForm : Form
    {
        #region Private Fields

        private static readonly string[] FILE_SEPARATORS = new string[] { Environment.NewLine, ",", ";", " " };

        private ModelManager manager;
        

        #endregion Private Fields

        #region Constructors, Initialization

        
        public MainForm()
        {
            InitializeComponent();
        }

        #endregion Constructors, Initialization

        #region Methods

        private void BuildView()
        {
            try
            {
                Cursor = Cursors.WaitCursor;
                this.treeView.BeginUpdate();
                this.treeView.Nodes.Clear();

                if (this.manager == null || this.manager.RootFiles == null)
                    return;

                if (this.rbLocation.Checked)
                    this.treeView.Nodes.Add(CreateNodeRec(this.manager.RootFolder));
                else
                    foreach (var file in this.manager.RootFiles)
                        this.treeView.Nodes.Add(CreateNodeRec(file));
            }
            finally
            {
                this.treeView.EndUpdate();
                Cursor = Cursors.Default;
            }
        }

        private TreeNode CreateNodeRec(HeaderFile file)
        {
            TreeNode node = new TreeNode(file.Name) { Tag = file };

            foreach (var childFile in file.DependOnMe)
                node.Nodes.Add(CreateNodeRec(childFile));

            return node;
        }

        private TreeNode CreateNodeRec(HeaderFolder folder)
        {
            TreeNode node = new TreeNode(folder.Name) { Tag = folder };

            //adding folders
            foreach (var childFolder in folder.Folders)
                node.Nodes.Add(CreateNodeRec(childFolder));

            //adding files
            foreach (var file in folder.Files)
                node.Nodes.Add(new TreeNode(file.Name) { Tag = file });

            return node;
        }

        private void CopySelectedFiles()
        {
            try
            {
                Cursor = Cursors.WaitCursor;

                //getting files that user selected
                List<HeaderFile> selectedFiles = ParseFileList().ToList();

                //collecting dependentFiles
                if (cbxCopyDependentFiles.Checked)
                    selectedFiles = CollectDependentFiles(selectedFiles);

                //ensuring directory is created
                string dstPath = tbxDstPath.Text.Trim();
                Directory.CreateDirectory(dstPath);

                //copying files
                foreach (var file in selectedFiles)
                    file.CopyTo(dstPath: dstPath,
                                keepFolderStructure: rbtnKeepFolders.Checked,
                                flatternHeaders: rbtnFlattern.Checked,
                                addHeaderPath: cbxAddFolder.Checked ? tbxPathToAdd.Text : "");


                var result = MessageBox.Show(String.Format("Successfully copied {0} files. Do you want to open dst folder now?", selectedFiles.Count),
                                                "Operation Completed", MessageBoxButtons.YesNo, MessageBoxIcon.Information);
                
                if (result == System.Windows.Forms.DialogResult.Yes)
                    Process.Start("explorer.exe", dstPath);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Failed to copy", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                Cursor = Cursors.Default;
            }

        }

        /// <summary>
        /// Enriches provided set of files with the files they relate on.
        /// </summary>
        /// <param name="selectedFiles">The collection of files to enrich</param>
        /// <returns>A new list that contains provided files and all dependent files.</returns>
        private List<HeaderFile> CollectDependentFiles(IEnumerable<HeaderFile> selectedFiles)
        {
            HashSet<HeaderFile> files = new HashSet<HeaderFile>();

            foreach (var file in selectedFiles)
                CollectDependentFilesRec(file, files);
                //foreach (var dependentFile in file.DependsOn)
                //    files.Add(dependentFile);

            return files.ToList();
        }

        private void CollectDependentFilesRec(HeaderFile header, HashSet<HeaderFile> collectedFiles)
        {
            collectedFiles.Add(header);

            foreach (var dependentFile in header.DependsOn)
            {
                if (collectedFiles.Contains(dependentFile))
                    continue;
                
                CollectDependentFilesRec(dependentFile, collectedFiles);
            }
        }

        private IEnumerable<HeaderFile> ParseFileList()
        {
            string[] filenames = this.tbxFilesToCopy.Text.Trim().Split(FILE_SEPARATORS, StringSplitOptions.RemoveEmptyEntries);
            
            foreach (var filename in filenames)
            {
                var file = this.manager.FindFile(filename);
                if (file != null)
                    yield return file;
                else
                    Console.WriteLine("File {0} was not found in model. Skipping.", filename);
            }
        }

        #endregion Methods

        #region Event Handlers

        private void btnSelectForlder_Click(object sender, EventArgs e)
        {
            using (var ofd = new FolderBrowserDialog() { SelectedPath = this.tbxRootPath.Text,
                                                        Description = "Select folder that should be scanned for headers."})
            {
                if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    this.tbxRootPath.Text = ofd.SelectedPath;
            }
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            try
            {
                Cursor = Cursors.WaitCursor;
                manager = new ModelManager() { RootPath = tbxRootPath.Text };
                BuildView();
                pnlCopy.Enabled = true;
            }
            catch (FileNotFoundException ex)
            {
                pnlCopy.Enabled = false;
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void rbLocation_CheckedChanged(object sender, EventArgs e)
        {
            BuildView();
        }

        private void cbxAddFolder_CheckedChanged(object sender, EventArgs e)
        {
            tbxPathToAdd.Enabled = cbxAddFolder.Checked;
        }

        private void btnSelectDstPath_Click(object sender, EventArgs e)
        {
            using (var ofd = new FolderBrowserDialog() { SelectedPath = this.tbxDstPath.Text, 
                                                        Description = "Select Folder where headers should be copied to." })
            {
                if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    this.tbxDstPath.Text = ofd.SelectedPath;
            }
        }
        
        private void tbxDstPath_TextChanged(object sender, EventArgs e)
        {
            btnCopy.Enabled = tbxDstPath.Text.Trim().Length > 0;
        }
        
        private void treeView_DoubleClick(object sender, EventArgs e)
        {

            var header = this.treeView.SelectedNode.Tag as HeaderFile;
            if (header == null)
                return;

            //checking if we have separator after last item (should we add all other possible separators?)
            if (this.tbxFilesToCopy.Text.Trim().Length > 0 
                &&!this.tbxFilesToCopy.Text.EndsWith(Environment.NewLine))
                this.tbxFilesToCopy.AppendText(Environment.NewLine);

            //it would be nice to insert detection that this file is already in the list here. But who cares?
            
            this.tbxFilesToCopy.AppendText(header.RelativePath + "," + Environment.NewLine);
        }
        
        private void btnCopy_Click(object sender, EventArgs e)
        {
            CopySelectedFiles();
        }

        #endregion Event Handlers
    }
}
