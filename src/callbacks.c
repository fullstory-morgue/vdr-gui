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
char IP[MAXLINE], IPfile[MAXLINE];


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
         strncpy(IPfile, "localhost", MAXLINE);  // IP;videodriver
     }
     else {
       fseek( fp, 0L, SEEK_SET );
       fscanf( fp, "%s", IPfile);
       printf("IP: %s, IPfile: %s\n", IP, IPfile);
       if( strncmp(IP, IPfile, MAXLINE) != 0 && strncmp(rw, "w", 1) == 0 ) {
          printf("config: %s\n", IP);
          fputs(IP, fp);
       }

       fclose(fp);
     }
  }
}

void
on_vdr_sxfe_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

    GtkWidget *entry           = lookup_widget(GTK_WIDGET(button), "IPEntry");
    gchar *video_driver        = gtk_combo_box_get_active_text(GTK_COMBO_BOX (
                                   lookup_widget (GTK_WIDGET (button), "combobox_driver")));

    strncpy(IP, gtk_entry_get_text(GTK_ENTRY(entry)), MAXLINE);
    strncat(IP, ":", MAXLINE);
    strncat(IP, video_driver, MAXLINE);
    strncat(IP, "\n", MAXLINE);

    vdrip_file("w");  // w for write the file

    system("/usr/share/aptosid-vdr/vdr-xine sxfe &");
}


void
on_vdr_sxfe_autostart_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
     system("printf '#!/bin/sh\n/usr/share/aptosid-vdr/vdr-xine sxfe' > $HOME/.kde/Autostart/vdr-xine-start;chmod +x $HOME/.kde/Autostart/vdr-xine-start\n");
}


void
on_vdr_sxfe_disable_autostart_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
     system("[ -e $HOME/.kde/Autostart/vdr-xine-start ] && rm -f $HOME/.kde/Autostart/vdr-xine-start");
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
     system("printf '#!/bin/sh\n/usr/share/aptosid-vdr/vdr-xine xine' > $HOME/.kde/Autostart/vdr-xine-start;chmod +x $HOME/.kde/Autostart/vdr-xine-start\n");
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
    system("/usr/share/aptosid-vdr/vdr-ip &");
}


void
on_udp_network_transport_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    system("[ -e $HOME/.aptosid-vdr.conf ] || touch $HOME/.aptosid-vdr.conf;\
            sed -ie '/^NetworkTransportMode.*/d' $HOME/.aptosid-vdr.conf;\
            echo 'NetworkTransportMode = 1' >> $HOME/.aptosid-vdr.conf");
}


void
on_allowclient_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
     char syscall[MAXLINE];

     strncpy( syscall, "#!/bin/bash\n", MAXLINE);
     strncat( syscall, "EDITOR=$(which kwrite)\n", MAXLINE);
     strncat( syscall, "[ -z \"$EDITOR\" ] && EDITOR=$(which gedit)\n", MAXLINE);
     strncat( syscall, "[ -z \"$EDITOR\" ] && EDITOR=$(which mousepad)\n", MAXLINE);
     strncat( syscall, "[ -z \"$EDITOR\" ] && EDITOR=x-terminal-emulator -e vi \n", MAXLINE);
     strncat( syscall, "su-to-root -X -c \"$EDITOR /etc/vdr/plugins/streamdevhosts.conf /etc/vdr/svdrphosts.conf\" &", MAXLINE);


     system( syscall);

     //system("su-to-root -X -c \"/usr/bin/kate \"/etc/vdr/plugins/streamdevhosts.conf /etc/vdr/svdrphosts.conf &\"");
}


void
on_network_transport_tcp_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    system("[ -e $HOME/.aptosid-vdr.conf ] || touch $HOME/.aptosid-vdr.conf;\
            sed -ie '/^NetworkTransportMode.*/d' $HOME/.aptosid-vdr.conf;\
            echo 'NetworkTransportMode = 0' >> $HOME/.aptosid-vdr.conf");
}


void
on_vdr_start_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-to-root -X -c \"/usr/bin/x-terminal-emulator -e /usr/share/aptosid-vdr/vdr-start\"");
}


void
on_vdr_stop_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-to-root -X -c \"x-terminal-emulator -e /usr/share/aptosid-vdr/vdr-stop\"");
}


void
on_channelslist_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-to-root -X -c \"/usr/share/aptosid-vdr/vdr-channelswitch\"");
}


void
on_wpvrscan_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-to-root -X -c \"x-terminal-emulator -e /usr/sbin/vdr-w_pvrscan pvrinput\"");
}


void
on_videodir_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    system("su-to-root -X -c \"x-terminal-emulator -e /usr/share/aptosid-vdr/vdr-videodir\"");
}


void
on_vdr_autostart_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
   char call[MAXLINE], root_or_not[MAXLINE];

   strncpy( call, "update-rc.d -f vdr remove;", MAXLINE);
   strncat( call, "update-rc.d -f vdr defaults 99;", MAXLINE);

   // root check
   if (!getenv("USER") || strncmp( getenv("USER"), "root", 4 ) == 0 )
       strncpy( root_or_not, call, MAXLINE);
   else {
       strncpy( root_or_not, "su-to-root -X -c \"", MAXLINE);
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

   // root check
   if (!getenv("USER") || strncmp( getenv("USER"), "root", 4 ) == 0 )
       strncpy( root_or_not, call, MAXLINE);
   else {
       strncpy( root_or_not, "su-to-root -X -c \"", MAXLINE);
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

   strncpy( call, "echo '#needed if_file_empty' >> /var/lib/vdr/aptosid-vdr/aptosid-vdr.conf;", MAXLINE);
   strncat( call, "sed -i -e '/LanguageMode/d' -e 'i\\LanguageMode = 0' -e '/./d' /var/lib/vdr/aptosid-vdr/aptosid-vdr.conf", MAXLINE);


   // root check
   if (!getenv("USER") || strncmp( getenv("USER"), "root", 4 ) == 0 )
       strncpy( root_or_not, call, MAXLINE);
   else {
       strncpy( root_or_not, "su-to-root -X -c \"", MAXLINE);
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

   strncpy( call, "echo '#needed if_file_empty' >> /var/lib/vdr/aptosid-vdr/aptosid-vdr.conf;", MAXLINE);
   strncat( call, "sed -i -e '/LanguageMode/d' -e 'i\\LanguageMode = 1' -e '/./d' /var/lib/vdr/aptosid-vdr/aptosid-vdr.conf", MAXLINE);


   // root check
   if (!getenv("USER") || strncmp( getenv("USER"), "root", 4 ) == 0 )
       strncpy( root_or_not, call, MAXLINE);
   else {
       strncpy( root_or_not, "su-to-root -X -c \"", MAXLINE);
       strncat( root_or_not, call, MAXLINE);
       strncat( root_or_not, "\"", MAXLINE);
   }

   system( root_or_not );

}


void
on_vdradmin_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
   system("/usr/share/aptosid-vdr/vdr-live &");
}


void
on_user_manual_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
      system("if [ $(echo $LANG|cut -c1-2) = de ]; then \
                    x-www-browser 'http://www.vdr-wiki.de/wiki/index.php/Benutzerhandbuch' & \
              else \
                    x-www-browser 'http://www.linuxtv.org/vdrwiki/index.php/VDR_User%27s_Manual' & \
              fi");
}


void
on_fullscreen_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    system("[ -e $HOME/.aptosid-vdr.conf ] || touch $HOME/.aptosid-vdr.conf;\
            sed -ie '/^XineFullscreen.*/d' $HOME/.aptosid-vdr.conf;\
            echo 'XineFullscreen = 1' >> $HOME/.aptosid-vdr.conf");
}


void
on_fullscreenoff_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
    system("[ -e $HOME/.aptosid-vdr.conf ] || touch $HOME/.aptosid-vdr.conf;\
            sed -ie '/^XineFullscreen.*/d' $HOME/.aptosid-vdr.conf;\
            echo 'XineFullscreen = 0' >> $HOME/.aptosid-vdr.conf");
}


void
on_update_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
    system("true");
}


gboolean
on_aptosid_eventbox1_button_press_event  (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
     system("if [ $(echo $LANG|cut -c1-2) = de ]; then \
                    x-www-browser 'http://aptosid.com/index.php?&newlang=deu' & \
              else \
                    x-www-browser 'http://aptosid.com/index.php?&newlang=eng' & \
              fi");

     return FALSE;
}


gboolean
on_vdr_eventbox2_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
      system("if [ $(echo $LANG|cut -c1-2) = de ]; then \
                    x-www-browser 'http://www.vdr-portal.de' & \
              else \
                    x-www-browser 'http://www.linuxtv.org/vdrwiki/index.php/Main_Page' & \
              fi");

      return FALSE;
}


void
gtk_combo_box_set_active_text (GtkComboBox *p_combo_box, 
                                const gchar *text) {
  gint i;
  gint nb_entry = 0;
  GtkTreeModel *p_tree_model = NULL;

  g_return_if_fail (p_combo_box);
  g_return_if_fail (text);

  p_tree_model = gtk_combo_box_get_model (p_combo_box);
  nb_entry = gtk_tree_model_iter_n_children (p_tree_model, NULL);
  for (i = 0; i < nb_entry; i++)
  {
    gtk_combo_box_set_active (p_combo_box, i);
    if (strcmp (gtk_combo_box_get_active_text (p_combo_box), text) == 0)
    {
      break;
    }
  }
  if (i == nb_entry)
  {
    gtk_combo_box_set_active (p_combo_box, 0);
  }
}


void
on_window1_realize                     (GtkWidget       *widget,
                                        gpointer         user_data)
{

  gchar *entry1 = "", *entry2 = "";
  char ip[MAXLINE];
  GtkWidget *entry = lookup_widget(GTK_WIDGET(widget), "IPEntry");

  vdrip_file("r");   // r for read the file

  // split IP and video driver

  strncpy( ip, IPfile, MAXLINE);
  entry1 = strtok(ip, ":");
  entry2 = strtok(NULL, ":");



  if ( entry1 == NULL || entry2 == NULL ) {
      if ( strlen( IPfile ) < 1 ) {
          strncpy( ip, "localhost", 9);
      }


      gtk_entry_set_text (GTK_ENTRY (entry), ip);
      gtk_combo_box_set_active(GTK_COMBO_BOX (
                      lookup_widget (GTK_WIDGET (widget), "combobox_driver")) ,0);
  }
  else {
      gtk_entry_set_text (GTK_ENTRY (entry), entry1);
      gtk_combo_box_set_active_text(GTK_COMBO_BOX (
                      lookup_widget (GTK_WIDGET (widget), "combobox_driver")), entry2);
  }

  return;
}

