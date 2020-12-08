#
# Regular cron jobs for the audio package
#
0 4	* * *	root	[ -x /usr/bin/audio_maintenance ] && /usr/bin/audio_maintenance
