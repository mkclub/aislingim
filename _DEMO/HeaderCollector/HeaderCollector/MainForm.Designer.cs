namespace HeaderCollector
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.btnSelectForlder = new System.Windows.Forms.Button();
            this.tbxRootPath = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.treeView = new System.Windows.Forms.TreeView();
            this.rbLocation = new System.Windows.Forms.RadioButton();
            this.rbDependency = new System.Windows.Forms.RadioButton();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.tbxFilesToCopy = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.btnSelectDstPath = new System.Windows.Forms.Button();
            this.tbxDstPath = new System.Windows.Forms.TextBox();
            this.pnlCopy = new System.Windows.Forms.Panel();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.cbxCopyDependentFiles = new System.Windows.Forms.CheckBox();
            this.rbtnMergeFolders = new System.Windows.Forms.RadioButton();
            this.rbtnKeepFolders = new System.Windows.Forms.RadioButton();
            this.btnCopy = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tbxPathToAdd = new System.Windows.Forms.TextBox();
            this.cbxAddFolder = new System.Windows.Forms.CheckBox();
            this.rbtnFlattern = new System.Windows.Forms.RadioButton();
            this.rbtnLeaveAsItIs = new System.Windows.Forms.RadioButton();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.pnlCopy.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnSelectForlder
            // 
            this.btnSelectForlder.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSelectForlder.Location = new System.Drawing.Point(442, 0);
            this.btnSelectForlder.Name = "btnSelectForlder";
            this.btnSelectForlder.Size = new System.Drawing.Size(43, 23);
            this.btnSelectForlder.TabIndex = 0;
            this.btnSelectForlder.Text = "...";
            this.btnSelectForlder.UseVisualStyleBackColor = true;
            this.btnSelectForlder.Click += new System.EventHandler(this.btnSelectForlder_Click);
            // 
            // tbxRootPath
            // 
            this.tbxRootPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tbxRootPath.Location = new System.Drawing.Point(106, 2);
            this.tbxRootPath.Name = "tbxRootPath";
            this.tbxRootPath.Size = new System.Drawing.Size(328, 20);
            this.tbxRootPath.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(0, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Headers root folder:";
            // 
            // treeView
            // 
            this.treeView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.treeView.Location = new System.Drawing.Point(0, 51);
            this.treeView.Name = "treeView";
            this.treeView.Size = new System.Drawing.Size(245, 361);
            this.treeView.TabIndex = 3;
            this.treeView.DoubleClick += new System.EventHandler(this.treeView_DoubleClick);
            // 
            // rbLocation
            // 
            this.rbLocation.AutoSize = true;
            this.rbLocation.Checked = true;
            this.rbLocation.Location = new System.Drawing.Point(52, 28);
            this.rbLocation.Name = "rbLocation";
            this.rbLocation.Size = new System.Drawing.Size(66, 17);
            this.rbLocation.TabIndex = 4;
            this.rbLocation.TabStop = true;
            this.rbLocation.Text = "Location";
            this.rbLocation.UseVisualStyleBackColor = true;
            this.rbLocation.CheckedChanged += new System.EventHandler(this.rbLocation_CheckedChanged);
            // 
            // rbDependency
            // 
            this.rbDependency.AutoSize = true;
            this.rbDependency.Location = new System.Drawing.Point(124, 28);
            this.rbDependency.Name = "rbDependency";
            this.rbDependency.Size = new System.Drawing.Size(86, 17);
            this.rbDependency.TabIndex = 4;
            this.rbDependency.TabStop = true;
            this.rbDependency.Text = "Dependency";
            this.rbDependency.UseVisualStyleBackColor = true;
            // 
            // btnRefresh
            // 
            this.btnRefresh.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnRefresh.Location = new System.Drawing.Point(272, 28);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(213, 32);
            this.btnRefresh.TabIndex = 7;
            this.btnRefresh.Text = "Read Model";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(55, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Copy files:";
            // 
            // tbxFilesToCopy
            // 
            this.tbxFilesToCopy.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tbxFilesToCopy.Location = new System.Drawing.Point(3, 16);
            this.tbxFilesToCopy.Multiline = true;
            this.tbxFilesToCopy.Name = "tbxFilesToCopy";
            this.tbxFilesToCopy.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbxFilesToCopy.Size = new System.Drawing.Size(242, 69);
            this.tbxFilesToCopy.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(0, 30);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Tree by:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 96);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(23, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "To:";
            // 
            // btnSelectDstPath
            // 
            this.btnSelectDstPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSelectDstPath.Location = new System.Drawing.Point(194, 91);
            this.btnSelectDstPath.Name = "btnSelectDstPath";
            this.btnSelectDstPath.Size = new System.Drawing.Size(43, 23);
            this.btnSelectDstPath.TabIndex = 0;
            this.btnSelectDstPath.Text = "...";
            this.btnSelectDstPath.UseVisualStyleBackColor = true;
            this.btnSelectDstPath.Click += new System.EventHandler(this.btnSelectDstPath_Click);
            // 
            // tbxDstPath
            // 
            this.tbxDstPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tbxDstPath.Location = new System.Drawing.Point(32, 93);
            this.tbxDstPath.Name = "tbxDstPath";
            this.tbxDstPath.Size = new System.Drawing.Size(156, 20);
            this.tbxDstPath.TabIndex = 1;
            this.tbxDstPath.TextChanged += new System.EventHandler(this.tbxDstPath_TextChanged);
            // 
            // pnlCopy
            // 
            this.pnlCopy.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pnlCopy.Controls.Add(this.groupBox2);
            this.pnlCopy.Controls.Add(this.btnCopy);
            this.pnlCopy.Controls.Add(this.groupBox1);
            this.pnlCopy.Controls.Add(this.label4);
            this.pnlCopy.Controls.Add(this.label2);
            this.pnlCopy.Controls.Add(this.tbxFilesToCopy);
            this.pnlCopy.Controls.Add(this.tbxDstPath);
            this.pnlCopy.Controls.Add(this.btnSelectDstPath);
            this.pnlCopy.Enabled = false;
            this.pnlCopy.Location = new System.Drawing.Point(248, 63);
            this.pnlCopy.Name = "pnlCopy";
            this.pnlCopy.Size = new System.Drawing.Size(248, 349);
            this.pnlCopy.TabIndex = 10;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.cbxCopyDependentFiles);
            this.groupBox2.Controls.Add(this.rbtnMergeFolders);
            this.groupBox2.Controls.Add(this.rbtnKeepFolders);
            this.groupBox2.Location = new System.Drawing.Point(7, 120);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(231, 89);
            this.groupBox2.TabIndex = 12;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "How to copy";
            // 
            // cbxCopyDependentFiles
            // 
            this.cbxCopyDependentFiles.AutoSize = true;
            this.cbxCopyDependentFiles.Checked = true;
            this.cbxCopyDependentFiles.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbxCopyDependentFiles.Location = new System.Drawing.Point(6, 67);
            this.cbxCopyDependentFiles.Name = "cbxCopyDependentFiles";
            this.cbxCopyDependentFiles.Size = new System.Drawing.Size(136, 17);
            this.cbxCopyDependentFiles.TabIndex = 1;
            this.cbxCopyDependentFiles.Text = "Copy included files also";
            this.toolTip.SetToolTip(this.cbxCopyDependentFiles, "If this is unchecked, only specified files will be copied");
            this.cbxCopyDependentFiles.UseVisualStyleBackColor = true;
            // 
            // rbtnMergeFolders
            // 
            this.rbtnMergeFolders.AutoSize = true;
            this.rbtnMergeFolders.Location = new System.Drawing.Point(6, 43);
            this.rbtnMergeFolders.Name = "rbtnMergeFolders";
            this.rbtnMergeFolders.Size = new System.Drawing.Size(175, 17);
            this.rbtnMergeFolders.TabIndex = 0;
            this.rbtnMergeFolders.TabStop = true;
            this.rbtnMergeFolders.Text = "Merge all files to specified folder";
            this.toolTip.SetToolTip(this.rbtnMergeFolders, "WARNING: If selected files set contains repeated files in different folders, they" +
        " will be overwritten!");
            this.rbtnMergeFolders.UseVisualStyleBackColor = true;
            // 
            // rbtnKeepFolders
            // 
            this.rbtnKeepFolders.AutoSize = true;
            this.rbtnKeepFolders.Checked = true;
            this.rbtnKeepFolders.Location = new System.Drawing.Point(6, 19);
            this.rbtnKeepFolders.Name = "rbtnKeepFolders";
            this.rbtnKeepFolders.Size = new System.Drawing.Size(128, 17);
            this.rbtnKeepFolders.TabIndex = 0;
            this.rbtnKeepFolders.TabStop = true;
            this.rbtnKeepFolders.Text = "Keep folders structure";
            this.rbtnKeepFolders.UseVisualStyleBackColor = true;
            // 
            // btnCopy
            // 
            this.btnCopy.Enabled = false;
            this.btnCopy.Location = new System.Drawing.Point(87, 321);
            this.btnCopy.Name = "btnCopy";
            this.btnCopy.Size = new System.Drawing.Size(75, 23);
            this.btnCopy.TabIndex = 11;
            this.btnCopy.Text = "Copy Files";
            this.btnCopy.UseVisualStyleBackColor = true;
            this.btnCopy.Click += new System.EventHandler(this.btnCopy_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.tbxPathToAdd);
            this.groupBox1.Controls.Add(this.cbxAddFolder);
            this.groupBox1.Controls.Add(this.rbtnFlattern);
            this.groupBox1.Controls.Add(this.rbtnLeaveAsItIs);
            this.groupBox1.Location = new System.Drawing.Point(7, 215);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(231, 100);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Modify Related Headers";
            // 
            // tbxPathToAdd
            // 
            this.tbxPathToAdd.Enabled = false;
            this.tbxPathToAdd.Location = new System.Drawing.Point(80, 65);
            this.tbxPathToAdd.Name = "tbxPathToAdd";
            this.tbxPathToAdd.Size = new System.Drawing.Size(145, 20);
            this.tbxPathToAdd.TabIndex = 2;
            this.toolTip.SetToolTip(this.tbxPathToAdd, "The path that should be added to each header.");
            // 
            // cbxAddFolder
            // 
            this.cbxAddFolder.AutoSize = true;
            this.cbxAddFolder.Location = new System.Drawing.Point(7, 67);
            this.cbxAddFolder.Name = "cbxAddFolder";
            this.cbxAddFolder.Size = new System.Drawing.Size(72, 17);
            this.cbxAddFolder.TabIndex = 1;
            this.cbxAddFolder.Text = "Add path:";
            this.toolTip.SetToolTip(this.cbxAddFolder, "The path that should be added to each header.");
            this.cbxAddFolder.UseVisualStyleBackColor = true;
            this.cbxAddFolder.CheckedChanged += new System.EventHandler(this.cbxAddFolder_CheckedChanged);
            // 
            // rbtnFlattern
            // 
            this.rbtnFlattern.AutoSize = true;
            this.rbtnFlattern.Location = new System.Drawing.Point(6, 42);
            this.rbtnFlattern.Name = "rbtnFlattern";
            this.rbtnFlattern.Size = new System.Drawing.Size(119, 17);
            this.rbtnFlattern.TabIndex = 0;
            this.rbtnFlattern.Text = "Leave only filename";
            this.toolTip.SetToolTip(this.rbtnFlattern, "WARNING: If selected files set contains repeated files in different folders, they" +
        " will be overwritten!");
            this.rbtnFlattern.UseVisualStyleBackColor = true;
            // 
            // rbtnLeaveAsItIs
            // 
            this.rbtnLeaveAsItIs.AutoSize = true;
            this.rbtnLeaveAsItIs.Checked = true;
            this.rbtnLeaveAsItIs.Location = new System.Drawing.Point(6, 19);
            this.rbtnLeaveAsItIs.Name = "rbtnLeaveAsItIs";
            this.rbtnLeaveAsItIs.Size = new System.Drawing.Size(110, 17);
            this.rbtnLeaveAsItIs.TabIndex = 0;
            this.rbtnLeaveAsItIs.TabStop = true;
            this.rbtnLeaveAsItIs.Text = "Leave as they are";
            this.rbtnLeaveAsItIs.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(497, 424);
            this.Controls.Add(this.pnlCopy);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.rbDependency);
            this.Controls.Add(this.rbLocation);
            this.Controls.Add(this.treeView);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbxRootPath);
            this.Controls.Add(this.btnSelectForlder);
            this.Name = "MainForm";
            this.Text = "Header Collector";
            this.pnlCopy.ResumeLayout(false);
            this.pnlCopy.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnSelectForlder;
        private System.Windows.Forms.TextBox tbxRootPath;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TreeView treeView;
        private System.Windows.Forms.RadioButton rbLocation;
        private System.Windows.Forms.RadioButton rbDependency;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbxFilesToCopy;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnSelectDstPath;
        private System.Windows.Forms.TextBox tbxDstPath;
        private System.Windows.Forms.Panel pnlCopy;
        private System.Windows.Forms.Button btnCopy;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox tbxPathToAdd;
        private System.Windows.Forms.CheckBox cbxAddFolder;
        private System.Windows.Forms.RadioButton rbtnFlattern;
        private System.Windows.Forms.RadioButton rbtnLeaveAsItIs;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox cbxCopyDependentFiles;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.RadioButton rbtnMergeFolders;
        private System.Windows.Forms.RadioButton rbtnKeepFolders;
    }
}

