using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Diagnostics;
using System.Threading;
using System.IO.Compression;
using Microsoft.Win32;

namespace Installer
{
    public partial class Form1 : Form
    {
		private int mirrorId = -1;
		private int currentWindow = 0;
		private int gameSelected = -1;
		private string gtaFolder = "";
		//private bool downloadLCC = true;
		private bool updater = false;

		public Form1(string[] args)
        {
            InitializeComponent();

			if(args.Length == 3)
			{
				currentWindow = 1;
				updater = true;
				gtaFolder = args[2];
				if (args[0] == "EFLC")
				{
					gameSelected = 0;
				}
				else
				{
					gameSelected = 1;
				}
				//if (args[1] != "LCC") downloadLCC = false;
				listBox1.Hide();
				listBox1.Items.Clear();
				listBox1.Items.AddRange(new object[] { "Official", "GitHub" });
				listBox1.Show();
				label3.Text = "Please select a download mirror, 2 available";
			}
		}

		public void runFile(string name, bool waitForExit)
		{
			if (File.Exists(gtaFolder + name))
			{
				try
				{
					Process processInfo = new Process();
					processInfo.StartInfo.WorkingDirectory = gtaFolder;
					processInfo.StartInfo.FileName = name;
					processInfo.StartInfo.CreateNoWindow = true;
					processInfo.Start();
					if(waitForExit) processInfo.WaitForExit();
				}
				catch (Exception e)
				{
					label3.Text = name + ": " + e.Message;
				}
			}
		}	

		public bool UnZip(string zipFile, string folderPath)
		{
			if (!File.Exists(zipFile))
			{
				MessageBox.Show("The Installer was unable to find the Client package\nPlease try using admin permissions or go to forum.iv-mp.eu for support",
					"Unable to open downloadd content", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return false;
			}

			if (!Directory.Exists(folderPath))
			{
				MessageBox.Show("The Installer was unable to open the installation folder you have selected\nPlease try using admin permissions", 
					"Unable to open the Installation folder", MessageBoxButtons.OK, MessageBoxIcon.Error);
				//Directory.CreateDirectory(folderPath);
				return false;
			}

			try
			{
				using (ZipArchive archive = ZipFile.OpenRead(zipFile))
				{
					foreach (ZipArchiveEntry file in archive.Entries)
					{
						string completeFileName = Path.Combine(folderPath, file.FullName);
						if (file.Name == "")
						{// Assuming Empty for Directory
							Directory.CreateDirectory(Path.GetDirectoryName(completeFileName));
							continue;
						}
						file.ExtractToFile(completeFileName, true);
					}
				}
			}
			catch(Exception e)
			{
				label3.Text = "The installation process failed. Please close IV:MP & GTA and try again.";
			}
			return true;
		}

		public void Download(string mirror, string tmpPath)
		{
			//this.label3.Text = mirror;
			using (WebClient wc = new WebClient())
			{
				//wc.UseDefaultCredentials = true;
				ServicePointManager.Expect100Continue = true;
				ServicePointManager.SecurityProtocol = (SecurityProtocolType)3072;

				wc.DownloadProgressChanged += progressChanged;
				wc.DownloadFileCompleted += tdownloadCompleted;
				wc.DownloadFileAsync(new System.Uri(mirror), tmpPath + "\\Client.zip");
			}
		}

		public bool isProcess(string name)
		{
			return Process.GetProcessesByName(name).Length > 0;
		}

		public void progressChanged(object sender, DownloadProgressChangedEventArgs e)
		{
			string buf = "Downloading: " + e.BytesReceived / (long)1024;
			if(e.TotalBytesToReceive != -1)
			{
				buf += "/" + e.TotalBytesToReceive / (long)1024;
			}
			buf += "kbs";
			this.label3.Text = buf;
		}

		public void tdownloadCompleted(object sender, AsyncCompletedEventArgs e)
		{
			if (e.Cancelled || e.Error != null)
			{
				this.label3.Text = "The download was canceled. Please try another mirror or join our site for manual downloads";
				MessageBox.Show(e.Error.Message + "\n " + e.Error.ToString(),
					"Download Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
			else
			{
				this.label3.Text = "Status: Download is complete, starting installation";

				while (isProcess("ivmpGameLauncher") || isProcess(getGameExecutable()))
				{
					MessageBox.Show("You need to close these programs first\n\n" + getGameExecutable() + "\n\nIVMP Game Launcher",
						"Please close these programs", MessageBoxButtons.OK, MessageBoxIcon.Error);
				}

				runFile("comMP\\Uninstall-IVMP.bat", true);

				if(gameSelected == 2) //complete edition
                {
					try
					{
						var registry = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, RegistryView.Registry64);
						var path = "SOFTWARE\\Rockstar Games";
						var rockstar = registry.CreateSubKey(path);
						var eflc = registry.CreateSubKey(path + "\\EFLC");
						eflc.SetValue("Design Installer", "1");
						eflc.SetValue("INSTALL_LANG", "1033");
						eflc.SetValue("InstallComplete", "1");
						eflc.SetValue("InstallFolder", gtaFolder);

						path = "SOFTWARE\\WOW6432Node\\Rockstar Games";
						rockstar = registry.CreateSubKey(path);
						eflc = registry.CreateSubKey(path + "\\EFLC");
						eflc.SetValue("InstallFolder", gtaFolder);
						eflc.SetValue("Design Installer", "1");
						eflc.SetValue("INSTALL_LANG", "1033");
						eflc.SetValue("InstallComplete", "1");

					}
					catch (Exception){}
				}

				if (UnZip(gtaFolder + "ivmpTemp\\Client.zip", gtaFolder))
				{
					this.label3.Text = "Status: installation completed.";
					Directory.Delete(gtaFolder + "ivmpTemp", true);
					runFile("ivmpGameLauncher.exe", false);
				}
				if (updater) System.Windows.Forms.Application.Exit();
			}
		}

		private string getGameExecutable()
		{
			return (gameSelected == 0 ? "EFLC" : "GTAIV");
		}

		private void button1_Click(object sender, EventArgs e)
		{
			if (currentWindow == 0) return;
			if(currentWindow == 1)
			{
				currentWindow = 0;
				button1.Enabled = button2.Enabled = false;
				label3.Text = "Select the GTA version you own, We recommend EFLC for it`s additional contents";
				listBox1.Hide();
				listBox1.Items.Clear();
				listBox1.Items.AddRange(new object[] { "GTA Episodes From Liberty City", "GTA IV", "GTA IV Complete Edition"});
				listBox1.Show();
			}
		}

		private void next_selectFolder()
		{
			bool b = false;
			while (!b)
			{
				gtaFolder = "";
				OpenFileDialog file = new OpenFileDialog();
				gameSelected = listBox1.SelectedIndex;
				string exec = getGameExecutable() + ".exe";
				file.Title = "Select the path of " + exec;
				file.FileName = exec;
				file.Filter = exec + "|" + exec;
				file.FilterIndex = 1;
				file.Multiselect = false;
				if (file.ShowDialog() == DialogResult.OK)
				{
					if (!file.FileName.EndsWith(exec) || file.FileName.EndsWith("Launch" + exec))
					{
						MessageBox.Show("Please select your " + exec,
							"Incorrect installation folder", MessageBoxButtons.OK, MessageBoxIcon.Error);
					}
					else
					{
						b = true;
						gtaFolder = file.FileName.Substring(0, file.FileName.Length - exec.Length);
					}
				}
				else
				{
					b = true;
				}
			}
			if (gtaFolder != "")
			{
				if (listBox1.SelectedIndex == -1) return;
				currentWindow++;
				button1.Enabled = true;
				button2.Enabled = false;
				listBox1.Hide();
				listBox1.Items.Clear();
				listBox1.Items.AddRange(new object[] { "Official", "GitHub" });
				listBox1.Show();
				label3.Text = "Please select a download mirror, 2 available";
			}

		}

		private void next_selectMirror()
		{
			mirrorId = listBox1.SelectedIndex;
			listBox1.Hide();
			button1.Enabled = button2.Enabled = false;
			label3.Text = "Status: creating ivmp temporary folders";

			string ivmpTemp = gtaFolder + "ivmpTemp";
			if (!Directory.Exists(ivmpTemp))
			{
				try
				{
					Directory.CreateDirectory(ivmpTemp);
				}
				catch (Exception ex)
				{
					string rs = "The Installer was unable to create its folder\n\nPlease try again using admin permissions\n\nDebug: " + gtaFolder + "\n" + ex.Message;
					MessageBox.Show(rs, "IVMP temporary folder failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
					return;
				}
			}

			string[,] mirrors = new string[3, 2] {
				{"https://bitbucket.org/Suge/eflc-mp-lua/downloads/IVMP_EFLC.zip",
					"https://bitbucket.org/Suge/eflc-mp-lua/downloads/IVMP_EFLC.zip" },
				
				{"https://bitbucket.org/Suge/eflc-mp-lua/downloads/IVMP_GTA4.zip",
					"https://bitbucket.org/Suge/eflc-mp-lua/downloads/IVMP_GTA4.zip"},
                {
					"https://bitbucket.org/BlueCat1/iv-mp-ce-download-link/downloads/IVMP_CE.zip",
					"https://bitbucket.org/BlueCat1/iv-mp-ce-download-link/downloads/IVMP_CE.zip"
				}
			};

			//int lccLink = downloadLCC ? 1 : 0;
			string mirror = mirrors[gameSelected, /*lccLink*/mirrorId];
			label3.Text = "Status: waiting for download to start";
			Download(mirror, ivmpTemp);
		}

		private void button2_Click(object sender, EventArgs e)
		{
			if (currentWindow == 0) next_selectFolder();
			else if (currentWindow == 1) next_selectMirror();
		}

		private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (currentWindow == 0) button2.Enabled = true;
			if (currentWindow == 1) button2.Enabled = true;
		}
	}
}
