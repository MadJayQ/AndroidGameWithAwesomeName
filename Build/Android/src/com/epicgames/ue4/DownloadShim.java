package com.epicgames.ue4;

import com.YourCompany.Project_Swaglord.OBBDownloaderService;
import com.YourCompany.Project_Swaglord.DownloaderActivity;


public class DownloadShim
{
	public static OBBDownloaderService DownloaderService;
	public static DownloaderActivity DownloadActivity;
	public static Class<DownloaderActivity> GetDownloaderType() { return DownloaderActivity.class; }
}

