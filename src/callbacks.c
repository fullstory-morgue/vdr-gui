#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

FILE* fp;
char IP[80], IPfile[80];


void vdrip_file(char *rw)
{

  if (!getenv("HOME")) {
     fprintf(stderr, "cd: HOME isn't defined\n");
     }
  else if (chdir(getenv("HOME")) < 0) {
     perror("cd");
     }
  else {
     fp=fopen("vdrip.conf", rw);  // rw for read or write the file
     if( fp == NULL ) {
         strcpy(IPfile, "localhost");
     }
     else {
       fseek( fp, 0L, SEEK_SET );
       fscanf( fp, "%s", IPfile);

       if( IP != IPfile && rw == "w" )
          fputs(IP, fp);

       fclose(fp);
     }
  }
}

void
on_vdr_sxfe_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 
    GtkWidget *entry = lookup_widget(GTK_WIDGET(button), "IPEntry");
    strcpy(IP, gtk_entry_get_text(GTK_ENTRY(entry)));
    vdrip_file("w");  // w for write the file

    system("vdr-xine sxfe &");
}


void
on_vdr_sxfe_autostart_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
     system("echo -e '#!/bin/sh\nvdr-xine sxfe' > $HOME/.kde/Autostart/vdr-xine-start;chmod +x $HOME/.kde/Autostart/vdr-xine-start");
}


void
on_vdr_sxfe_disable_autostart_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
     system("[ -e $HOME/.kde/Autostart/vdr-xine-start ] && rm -f $HOME/.kde/Autostart/vdr-xine-start");
}


void
on_xine_ui_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry = lookup_widget(GTK_WIDGET(button), "IPEntry");
    strcpy(IP, gtk_entry_get_text(GTK_ENTRY(entry)));
    vdrip_file("w");  // w for write the file

    system("vdr-xine xine &");
}


void
on_keymap_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
    system("x-terminal-emulator -e vdr-xine-keymap &");
}


void
on_xine_ui_autostart_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
     system("echo -e '#!/bin/sh\nvdr-xine xine' > $HOME/.kde/Autostart/vdr-xine-start;chmod +x $HOME/.kde/Autostart/vdr-xine-start");
}


void
on_xine_ui_disable_autostart_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
     system("[ -e $HOME/.kde/Autostart/vdr-xine-start ] && rm -f $HOME/.kde/Autostart/vdr-xine-start");
}


void
on_vdr_ip_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
    system("/usr/sbin/vdr-ip &");
}


void
on_udp_network_transport_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    system("[ -e $HOME/.sidux-vdr.conf ] || touch $HOME/.sidux-vdr.conf;\
            sed -ie '/^NetworkTransportMode.*/d' $HOME/.sidux-vdr.conf;\
            echo 'NetworkTransportMode = 1' >> $HOME/.sidux-vdr.conf");
}


void
on_allowclient_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
   system("su-me kwrite /etc/vdr/plugins/streamdevhosts.conf /etc/vdr/svdrphosts.conf &");
}


void
on_network_transport_tcp_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    system("[ -e $HOME/.sidux-vdr.conf ] || touch $HOME/.sidux-vdr.conf;\
            sed -ie '/^NetworkTransportMode.*/d' $HOME/.sidux-vdr.conf;\
            echo 'NetworkTransportMode = 0' >> $HOME/.sidux-vdr.conf");
}


void
on_vdr_start_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-me x-terminal-emulator -e /usr/sbin/vdr-start");
}


void
on_vdr_stop_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-me x-terminal-emulator -e /usr/sbin/vdr-stop");
}


void
on_channelslist_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-me /usr/sbin/vdr-channelswitch");
}


void
on_wpvrscan_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-me x-terminal-emulator -e /usr/sbin/vdr-w_pvrscan pvrinput");
}


void
on_videodir_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-me x-terminal-emulator -e /usr/sbin/vdr-videodir");
}


void
on_vdr_autostart_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
   system("su-me \" \
	update-rc.d -f vdr remove; \
	update-rc.d -f vdradmin-am remove; \
	update-rc.d -f vdr defaults 99; \
	update-rc.d -f vdradmin-am defaults 99\"");
}


void
on_vdr_disable_autostart_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
   system("su-me \" \
	update-rc.d -f vdr remove; \
	update-rc.d -f vdradmin-am remove\"");
}


void
on_language_automatic_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-me \"echo '#needed if_file_empty' >> /var/lib/vdr/sidux-vdr/sidux-vdr.conf; \
            sed -i -e '/LanguageMode/d' -e 'i\LanguageMode = 0' -e '/./d' /var/lib/vdr/sidux-vdr/sidux-vdr.conf\"");
}


void
on_language_manuel_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-me \"echo '#needed if_file_empty' >> /var/lib/vdr/sidux-vdr/sidux-vdr.conf; \
            sed -i -e '/LanguageMode/d' -e 'i\LanguageMode = 1' -e '/./d' /var/lib/vdr/sidux-vdr/sidux-vdr.conf\"");
}


void
on_vdradmin_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
   system("vdr-vdradmin &");
}


void
on_user_manual_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
      system("if [ $(echo $LANGUAGE|cut -c1-2) = de ]; then \
                    x-www-browser 'http://www.vdr-wiki.de/wiki/index.php/Benutzerhandbuch' & \
              else \
                    x-www-browser 'http://www.linuxtv.org/vdrwiki/index.php/VDR_User%27s_Manual' & \
              fi");
}


void
on_fullscreen_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    system("[ -e $HOME/.sidux-vdr.conf ] || touch $HOME/.sidux-vdr.conf;\
            sed -ie '/^XineFullscreen.*/d' $HOME/.sidux-vdr.conf;\
            echo 'XineFullscreen = 1' >> $HOME/.sidux-vdr.conf");
}


void
on_fullscreenoff_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
    system("[ -e $HOME/.sidux-vdr.conf ] || touch $HOME/.sidux-vdr.conf;\
            sed -ie '/^XineFullscreen.*/d' $HOME/.sidux-vdr.conf;\
            echo 'XineFullscreen = 0' >> $HOME/.sidux-vdr.conf");
}


void
on_update_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-me x-terminal-emulator -e /usr/sbin/vdr-update");
}


gboolean
on_sidux_eventbox1_button_press_event  (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
     system("if [ $(echo $LANGUAGE|cut -c1-2) = de ]; then \
                    x-www-browser 'http://www.sidux.com/index.php?&newlang=deu' & \
              else \
                    x-www-browser 'http://www.sidux.com/index.php?&newlang=eng' & \
              fi");

     return FALSE;
}


gboolean
on_vdr_eventbox2_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
      system("if [ $(echo $LANGUAGE|cut -c1-2) = de ]; then \
                    x-www-browser 'http://www.vdr-portal.de' & \
              else \
                    x-www-browser 'http://www.linuxtv.org/vdrwiki/index.php/Main_Page' & \
              fi");

      return FALSE;
}


void
on_IPEntry_activate                    (GtkEntry        *entry,
                                        gpointer         user_data)
{

}


gboolean
on_window1_configure_event             (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data)
{

  GtkWidget *entry = lookup_widget(GTK_WIDGET(widget), "IPEntry");

  vdrip_file("r");   // r for read the file
  gtk_entry_set_text (GTK_ENTRY (entry), IPfile);

  return FALSE;
}
