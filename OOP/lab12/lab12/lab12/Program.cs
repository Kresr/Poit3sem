using System;
using static System.Net.Mime.MediaTypeNames;
using System.IO;
using System.Reflection;
using System.Collections.Specialized;
using System.IO.Compression;
using System.Data.SqlTypes;

namespace Lab12
{
    public static class YSALog
    {
        static string logfile = "YSAlogfile.txt";

        public static void Write(string method, string filename = null)
        {
            string textFromLogFile = Read();
            textFromLogFile += $"Date - {DateTime.Now}" + (filename != null ? $"\nFile - {filename} \n" : "\n")
                + $"Method - {method}\n";

            using (StreamWriter writer = new StreamWriter(logfile, false))
            {
                writer.WriteLine(textFromLogFile);
            }
        }

        public static string Read()
        {
            using (StreamReader reader = new StreamReader(logfile))
            {
                string text = reader.ReadToEnd();
                return text;
            }
        }

        public static bool Find(string str)
        {
            string text = Read();
            if (text.IndexOf(str) != -1)
            {
                return true;
            }
            return false;
        }
    }

    public class YSADiskInfo
    {
        public static void GetFreeDiskSpace(string driveName)
        {
            DriveInfo drive = new DriveInfo(driveName);
            if (drive.IsReady)
            {
                Console.WriteLine($"Свободное место на диске {drive.Name}: {drive.AvailableFreeSpace / (1024 * 1024 * 1024)} ГБ");
            }
            else
            {
                Console.WriteLine($"Диск {driveName} недоступен.");
            }
        }

        public static void GetFileSystemInfo(string driveName)
        {
            DriveInfo drive = new DriveInfo(driveName);
            if (drive.IsReady)
            {
                Console.WriteLine($"Файловая система на диске {drive.Name}: {drive.DriveFormat}");
            }
            else
            {
                Console.WriteLine($"Диск {driveName} недоступен.");
            }
        }

        public static void GetAllDrivesInfo()
        {
            DriveInfo[] drives = DriveInfo.GetDrives();
            foreach (DriveInfo drive in drives)
            {
                if (drive.IsReady)
                {
                    Console.WriteLine($"Диск: {drive.Name}");
                    Console.WriteLine($"Файловая система: {drive.DriveFormat}");
                    Console.WriteLine($"Полный объем: {drive.TotalSize / (1024 * 1024 * 1024)} ГБ");
                    Console.WriteLine($"Доступный объем: {drive.AvailableFreeSpace / (1024 * 1024 * 1024)} ГБ");
                    Console.WriteLine($"Метка тома: {drive.VolumeLabel}");
                    Console.WriteLine();
                }
                else
                {
                    Console.WriteLine($"Диск {drive.Name} недоступен.");
                }
            }
        }
    }

    public class YSAFileInfo
    {
        public static void GetFullPath(string filePath)
        {
            if (File.Exists(filePath))
            {
                FileInfo fileInfo = new FileInfo(filePath);
                Console.WriteLine($"Полный путь: {fileInfo.FullName}");
            }
            else
            {
                Console.WriteLine("Файл не существует.");
            }
        }

        public static void GetBasicInfo(string filePath)
        {
            if (File.Exists(filePath))
            {
                FileInfo fileInfo = new FileInfo(filePath);
                Console.WriteLine($"Имя файла: {fileInfo.Name}");
                Console.WriteLine($"Размер файла: {fileInfo.Length} байт");
                Console.WriteLine($"Расширение файла: {fileInfo.Extension}");
            }
            else
            {
                Console.WriteLine("Файл не существует.");
            }
        }

        public static void GetFileInfo(string filePath)
        {
            if (File.Exists(filePath))
            {
                FileInfo fileInfo = new FileInfo(filePath);
                Console.WriteLine($"Дата создания: {fileInfo.CreationTime}");
                Console.WriteLine($"Дата последнего изменения: {fileInfo.LastWriteTime}");
            }
            else
            {
                Console.WriteLine("Файл не существует.");
            }
        }
    }

    public class YSADirInfo
    {
        public static void GetDirInfo(string dirName)
        {
            DirectoryInfo dirInfo = new DirectoryInfo(dirName);
            Console.WriteLine("\nDir name:       " + dirInfo.Name +
                              "\nFiles amount:   " + dirInfo.GetFiles().Length +
                              "\nCreating time:  " + dirInfo.LastWriteTime +
                              "\nSubDirs amount: " + dirInfo.GetDirectories().Length +
                              "\nParent dir: " + dirInfo.Parent.Name);
            YSALog.Write("GetFileInfo", dirName);
        }
    }

    public class YSAFileManager
    {
        public static void GetAllFilesAndDir(string driveName)
        {
            if (!Directory.Exists(driveName))
            {
                Console.WriteLine("Диск не существует.");
                return;
            }

            string inspectDir = Path.Combine(driveName, "YSAInspect");
            Directory.CreateDirectory(inspectDir);

            string filePath = Path.Combine(inspectDir, "YSAdirinfo.txt");
            using (StreamWriter writer = new StreamWriter(filePath))
            {
                writer.WriteLine("Список файлов и папок:");
                foreach (var directory in Directory.GetDirectories(driveName))
                {
                    writer.WriteLine("Директория: " + directory);
                }
                foreach (var file in Directory.GetFiles(driveName))
                {
                    writer.WriteLine("Файл: " + file);
                }
            }

            string copyFilePath = Path.Combine(inspectDir, "YSAdirinfo_copy.txt");
            if (File.Exists(copyFilePath))
            {
                File.Delete(copyFilePath);
            }
            File.Copy(filePath, copyFilePath);
            File.Delete(filePath);
        }

        public static void CopyFilesWithExtension(string sourceDir, string extension)
        {
            if (!Directory.Exists(sourceDir))
            {
                Console.WriteLine("Исходный каталог не существует.");
                return;
            }

            string filesDir = Path.Combine(sourceDir, "YSAFiles");
            Directory.CreateDirectory(filesDir);

            foreach (var file in Directory.GetFiles(sourceDir, $"*{extension}"))
            {
                string fileName = Path.GetFileName(file);
                string destFile = Path.Combine(filesDir, fileName);
                File.Copy(file, destFile, true);
            }

            string inspectDir = Path.Combine(sourceDir, "YSAInspect");
            if (!Directory.Exists(inspectDir))
            {
                Directory.CreateDirectory(inspectDir);
            }

            string newFilesDir = Path.Combine(inspectDir, "YSAFiles");
            if (Directory.Exists(newFilesDir))
            {
                Directory.Delete(newFilesDir, true);
            }
            Directory.Move(filesDir, newFilesDir);
        }

        public static void ArchiveAndExtractFiles(string sourceDir)
        {
            string filesDir = Path.Combine(sourceDir, "YSAInspect", "YSAFiles");

            if (!Directory.Exists(filesDir))
            {
                Console.WriteLine("Каталог YSAFiles не найден.");
                return;
            }

            string zipPath = Path.Combine(sourceDir, "YSAFiles.zip");
            if (File.Exists(zipPath))
            {
                File.Delete(zipPath);
            }
            ZipFile.CreateFromDirectory(filesDir, zipPath);

            string extractPath = Path.Combine(sourceDir + "", "ExtractedFiles");
            if (Directory.Exists(extractPath))
            {
                Directory.Delete(extractPath, true);
            }
            Directory.CreateDirectory(extractPath);

            ZipFile.ExtractToDirectory(zipPath, extractPath);

            Console.WriteLine("Архивирование и разархивирование выполнено успешно.");
        }
    }

    internal class Program
    {
        public static void Main(string[] args)
        {
            YSADiskInfo.GetFreeDiskSpace("D");
            YSAFileInfo.GetFullPath("lab12.exe");
            YSAFileInfo.GetFileInfo("lab12.exe");
            YSADirInfo.GetDirInfo("test");
            YSAFileManager.GetAllFilesAndDir("..\\net8.0");
            YSAFileManager.CopyFilesWithExtension("..\\net8.0", ".txt");
            YSAFileManager.ArchiveAndExtractFiles("..\\net8.0");
        }
    }
}
