using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace HeaderCollector.Model
{
    class ModelManager
    {
        #region Constants

        internal static readonly string[] HEADER_EXTENSIONS = new string[] { "*.h", "*.hpp" };

        #endregion Constants

        #region Private Fields

        private List<HeaderFile> rootHeaders = new List<HeaderFile>();
        private HeaderFolder rootFolder;

        #endregion Private Fields

        #region Constructors, Initialization
        #endregion Constructors, Initialization

        #region Properties

        public string RootPath
        {
            get { return this.rootFolder != null ? this.rootFolder.Path : ""; }
            set
            {
                if (this.rootFolder != null && this.rootFolder.Path == value)
                    return;

                BuildModel(value);
            }
        }

        public HeaderFolder RootFolder
        {
            get { return this.rootFolder; }
        }

        public IEnumerable<HeaderFile> RootFiles
        {
            get { return this.rootHeaders; }
        }

        #endregion Properties

        #region Methods

        private void Clear()
        {
            this.rootFolder = null;
            this.rootHeaders.Clear();
        }

        private void BuildModel(string path)
        {
            if (this.rootFolder != null)
                Clear();

            if (!Directory.Exists(path))
                throw new FileNotFoundException("Path " + path + " is not valid!");

            this.rootFolder = new HeaderFolder(path);

            CollectRootHeaders();
        }

        private void CollectRootHeaders()
        {
            //var nameToHeaderMap = this.rootFolder.AllFiles().ToDictionary(file => file.FilePath);
            var nameToHeaderMap = new Dictionary<string, List<HeaderFile>>();
            foreach (var file in this.rootFolder.AllFiles())
            {
                if (!nameToHeaderMap.ContainsKey(file.Name))
                    nameToHeaderMap.Add(file.Name.ToLower(), new List<HeaderFile>());

                nameToHeaderMap[file.Name.ToLower()].Add(file);
            }

            foreach (var file in this.rootFolder.AllFiles())
            {
                file.SatisfyDependencies(nameToHeaderMap);

                if (!file.DependsOn.Any())
                    this.rootHeaders.Add(file);
            }
        }

        public HeaderFile FindFile(string partialFilename)
        {
            if (this.RootFolder == null)
                return null;

            var formattedPartialFilename = partialFilename
                                                    .Trim()
                                                    .Replace('/', Path.DirectorySeparatorChar)
                                                    .ToLower();

            return this.rootFolder.FindFile(formattedPartialFilename);
        }

        #endregion Methods

        
    }
}
