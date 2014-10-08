package nl.rolfhut.scat.android.app;

import nl.rolfhut.scat.android.cloud.WebHelpers;
import nl.rolfhut.scat.android.storage.Prefs;
import nl.rolfhut.scat.android.storage.TinkerPrefs;
import android.app.Application;


public class SparkCoreApp extends Application {

	@Override
	public void onCreate() {
		super.onCreate();

		AppConfig.initialize(this);
		Prefs.initialize(this);
		TinkerPrefs.initialize(this);
		WebHelpers.initialize(this);
		DeviceState.initialize(this);
	}

}
