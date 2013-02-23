using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace HeaderCollector.Model
{
    class HeaderFolder
    {
        #region Private Fields

        private HeaderFolder parentFolder;
        private List<HeaderFolder> folders = new List<HeaderFolder>();
        private List<HeaderFile> files = new List<HeaderFile>();

        #endregion Private Fields

        #region Constructors, Initialization
        
        public HeaderFolder(string path)
        {
            this.Path = path;
            BuildTree();
        }

        internal HeaderFolder(string path, HeaderFolder parentFolder):this(path)
        {
            this.parentFolder = parentFolder;
        }

        public void BuildTree()
        {
            //clearing
            if (this.folders.Count > 0)
                this.folders.Clear();
            if (this.files.Count > 0)
                this.files.Clear();

            //collecting folders
            foreach (var dir in Directory.EnumerateDirectories(Path))
            {
                var folder = new HeaderFolder(dir, this);
                if(folder.files.Count > 0 || folder.folders.Count > 0)
                    this.folders.Add(folder);
            }

            //collecting header files.
            foreach (var extension in ModelManager.HEADER_EXTENSIONS)
                foreach (var file in Directory.EnumerateFiles(Path, extension))
                    files.Add(new HeaderFile(this, file));

            //ordering items.
            this.folders = this.folders.OrderBy(folder => folder.Name.ToLower()).ToList();
            this.files = this.files.OrderBy(file=>file.Name.ToLower()).ToList();
        }

        #endregion Constructors, Initialization

        #region Properties

        public string Path { get; private set; }

        public IEnumerable<HeaderFolder> Folders
        {
            get { return this.folders; }
        }

        public IEnumerable<HeaderFile> Files
        {
            get { return this.files; }
        }

        public string Name { get { return System.IO.Path.GetFileName(Path); } }

        internal string RootFolder
        {
            get { return this.parentFolder == null ? this.Path : this.parentFolder.RootFolder; }
        }

        #endregion Properties

        #region Methods

        public IEnumerable<HeaderFile> AllFiles()
        {
            foreach(var file in files)
                yield return file;

            foreach (var folder in folders)
                foreach (var file in folder.AllFiles())
                    yield return file;
        }

        public HeaderFile FindFile(string partialFilename)
        {
            //searching our files
            foreach (var file in this.files)
                if (file.FilePath.ToLower().EndsWith(partialFilename))
                    return file;

            //searching folders
            foreach (var folder in this.folders)
            {
                var file = folder.FindFile(partialFilename);
                if (file != null)
                    return file;
            }

            //sorry, no luck.
            return null;
        }

        public override string ToString()
        {
            return Name;
        }

        #endregion Methods

        
    }
}
