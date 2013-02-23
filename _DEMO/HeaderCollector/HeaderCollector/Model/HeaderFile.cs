using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace HeaderCollector.Model
{
    class HeaderFile
    {
        private readonly Regex HEADER_REGEX = new Regex("#[ \\t]*include[ \\t]*\\\"(.*)\\\"", RegexOptions.IgnoreCase);

        #region Private Fields

        private HeaderFolder parentFolder;
        private String name;
        private String path;
        private List<HeaderFile> dependsOn = new List<HeaderFile>();
        private List<HeaderFile> dependOnMe = new List<HeaderFile>();

        #endregion Private Fields

        #region Constructors, Initialization

        public HeaderFile(HeaderFolder parentFolder, string path)
        {
            this.path = path;
            this.name = Path.GetFileName(path);
            this.parentFolder = parentFolder;
        }

        #endregion Constructors, Initialization

        #region Properties

        public string Name { get { return this.name; } }

        public string FilePath { get { return this.path; } }

        public string RelativePath
        {
            get
            {
                return this.path.Replace(this.parentFolder.RootFolder+ Path.DirectorySeparatorChar, "");
            }
        }

        public IEnumerable<HeaderFile> DependsOn { get { return this.dependsOn; } }

        public IEnumerable<HeaderFile> DependOnMe { get { return this.dependOnMe; } }
        
        #endregion Properties

        #region Methods

        public void SatisfyDependencies(Dictionary<string, List<HeaderFile>> nameToFileMap)
        {
            foreach (var dependency in CollectDependencies())
            {
                var fileName = Path.GetFileName(dependency);

                if (!nameToFileMap.ContainsKey(fileName))
                {
                    Console.WriteLine("DEPENDENCY " + dependency + " was not foud for class " + name + "!");
                    continue;
                }

                HeaderFile selectedFile = null;

                foreach (var file in nameToFileMap[fileName])
                    if (file.path.ToLower().EndsWith(dependency))
                    {
                        selectedFile = file;
                        break;
                    }

                if (selectedFile != null)
                {
                    this.dependsOn.Add(selectedFile);
                    selectedFile.dependOnMe.Add(this);
                }
                else
                    Console.WriteLine("DEPENDENCY " + dependency + " was not foud for class " + name + ". However, "+nameToFileMap[fileName].Count+" options were available!");
            }
        }

        public void CopyTo(string dstPath, bool keepFolderStructure, bool flatternHeaders, string addHeaderPath)
        {
            //selecting new file name
            string dstFilename = Path.Combine(dstPath, keepFolderStructure ? RelativePath : Name);

            Directory.CreateDirectory(Path.GetDirectoryName(dstFilename));

            if (File.Exists(dstFilename))
                Console.WriteLine("WARNING: overwriting file {0} with file {1}", dstFilename, this.path);

            if (!flatternHeaders && String.IsNullOrEmpty(addHeaderPath))
                File.Copy(this.path, dstFilename, overwrite: true);
            else
            {//no, we have to process headers as well.
                using(var reader = new StreamReader(this.path))
                using (var writer = new StreamWriter(dstFilename))
                {
                    writer.Write(HEADER_REGEX.Replace(reader.ReadToEnd(),
                        (match)=>
                        {
                            var res = match.Groups[1].Value.Replace('/', Path.DirectorySeparatorChar);

                            if (!HasDependency(res))
                                return match.Value;
                            
                            if(flatternHeaders)
                                res = Path.GetFileName(res);
                            if(!String.IsNullOrEmpty(addHeaderPath))
                                res = Path.Combine(addHeaderPath, res);

                            return match.Value.Replace(match.Groups[1].Value, res);
                        }));
                }
            }
        }

        private bool HasDependency(string path)
        {
            foreach (var file in this.dependsOn)
                if (file.path.EndsWith(path))
                    return true;

            return false;
        }

        private IEnumerable<string> CollectDependencies()
        {
            Regex regex = HEADER_REGEX;
            
            using (var reader = new StreamReader(this.path))
                while (!reader.EndOfStream)
                    foreach (Match match in regex.Matches(reader.ReadLine()))//maybe we should read to end here?
                        yield return match.Groups[1].Value.Replace('/', Path.DirectorySeparatorChar).ToLower();
        }
        
        public override string ToString()
        {
            return name;
        }
        #endregion Methods

        
    }
}
