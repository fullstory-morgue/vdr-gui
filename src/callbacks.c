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

#define MAXLINE 1024

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

    system("/usr/sbin/vdr-xine sxfe &");
}


void
on_vdr_sxfe_autostart_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
     system("echo -e '#!/bin/sh\n/usr/sbin/vdr-xine sxfe' > $HOME/.kde/Autostart/vdr-xine-start;chmod +x $HOME/.kde/Autostart/vdr-xine-start");
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

    system("/usr/sbin/vdr-xine xine &");
}


void
on_keymap_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
    system("x-terminal-emulator -e /usr/sbin/vdr-xine-keymap &");
}


void
on_xine_ui_autostart_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
     system("echo -e '#!/bin/sh\n/usr/sbin/vdr-xine xine' > $HOME/.kde/Autostart/vdr-xine-start;chmod +x $HOME/.kde/Autostart/vdr-xine-start");
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
   char call[MAXLINE], root_or_not[MAXLINE];

   strncpy( call, "update-rc.d -f vdr remove;", MAXLINE);
   strncat( call, "update-rc.d -f vdradmin-am remove;", MAXLINE);
   strncat( call, "update-rc.d -f vdr defaults 99;", MAXLINE);
   strncat( call, "update-rc.d -f vdradmin-am defaults 99", MAXLINE);

   // root check
   if (!getenv("USER") || strncmp( getenv("USER"), "root", 4 ) == 0 )
       strncpy( root_or_not, call, MAXLINE);
   else {
       strncpy( root_or_not, "su-me \"", MAXLINE);
       strncat( root_or_not, call, MAXLINE);
       strncat( root_or_not, "\"", MAXLINE);
   }

   system( root_or_not );
}


void
on_vdr_disable_autostart_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
   char call[MAXLINE], root_or_not[MAXLINE];

   strncpy( call, "update-rc.d -f vdr remove;", MAXLINE);
   strncat( call, "update-rc.d -f vdradmin-am remove", MAXLINE);

   // root check
   if (!getenv("USER") || strncmp( getenv("USER"), "root", 4 ) == 0 )
       strncpy( root_or_not, call, MAXLINE);
   else {
       strncpy( root_or_not, "su-me \"", MAXLINE);
       strncat( root_or_not, call, MAXLINE);
       strncat( root_or_not, "\"", MAXLINE);
   }

   system( root_or_not );
}


void
on_language_automatic_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

   char call[MAXLINE], root_or_not[MAXLINE];

   strncpy( call, "echo '#needed if_file_empty' >> /var/lib/vdr/sidux-vdr/sidux-vdr.conf;", MAXLINE);
   strncat( call, "sed -i -e '/LanguageMode/d' -e 'i\\LanguageMode = 0' -e '/./d' /var/lib/vdr/sidux-vdr/sidux-vdr.conf", MAXLINE);


   // root check
   if (!getenv("USER") || strncmp( getenv("USER"), "root", 4 ) == 0 )
       strncpy( root_or_not, call, MAXLINE);
   else {
       strncpy( root_or_not, "su-me \"", MAXLINE);
       strncat( root_or_not, call, MAXLINE);
       strncat( root_or_not, "\"", MAXLINE);
   }

   system( root_or_not );

}


void
on_language_manuel_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

   char call[MAXLINE], root_or_not[MAXLINE];

   strncpy( call, "echo '#needed if_file_empty' >> /var/lib/vdr/sidux-vdr/sidux-vdr.conf;", MAXLINE);
   strncat( call, "sed -i -e '/LanguageMode/d' -e 'i\\LanguageMode = 1' -e '/./d' /var/lib/vdr/sidux-vdr/sidux-vdr.conf", MAXLINE);


   // root check
   if (!getenv("USER") || strncmp( getenv("USER"), "root", 4 ) == 0 )
       strncpy( root_or_not, call, MAXLINE);
   else {
       strncpy( root_or_not, "su-me \"", MAXLINE);
       strncat( root_or_not, call, MAXLINE);
       strncat( root_or_not, "\"", MAXLINE);
   }

   system( root_or_not );

}


void
on_vdradmin_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
   system("/usr/sbin/vdr-vdradmin &");
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
                    x-www-browser 'http://sidux.com/index.php?&newlang=deu' & \
              else \
                    x-www-browser 'http://sidux.com/index.php?&newlang=eng' & \
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
