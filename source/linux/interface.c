#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

GtkWidget* create_mainwindow (void) {

	GtkWidget *window;
	GtkWidget *box;

	GtkWidget *menubar;
	//GtkWidget *sep;
  
	GtkWidget *filemenu;
	GtkWidget *file;
	GtkWidget *open;
	GtkWidget *quit;
	
	GtkWidget *emulatormenu;
	GtkWidget *emulator;
	GtkWidget *run;
	GtkWidget *pause;
	GtkWidget *savestate;
	GtkWidget *loadstate;
	GtkWidget *cheats;
	
	GtkWidget *configurationmenu;
	GtkWidget *configuration;
	GtkWidget *videoconfig;
	GtkWidget *audioconfig;
	GtkWidget *inputconfig;
	GtkWidget *miscconfig;

	GtkWidget *helpmenu;
	GtkWidget *help;
	GtkWidget *about;
	
	GtkWidget *drawingarea;
	
	GtkWidget *statusbar;

	//gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
	gtk_window_set_title(GTK_WINDOW(window), "Nestopia Undead");

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	menubar = gtk_menu_bar_new();
	//sep = gtk_separator_menu_item_new();
	filemenu = gtk_menu_new();
	emulatormenu = gtk_menu_new();
	configurationmenu = gtk_menu_new();
	helpmenu = gtk_menu_new();

	file = gtk_menu_item_new_with_label("File");
	open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
	quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
	
	emulator = gtk_menu_item_new_with_label("Emulator");
	run = gtk_menu_item_new_with_label("Run");
	pause = gtk_menu_item_new_with_label("Pause");
	savestate = gtk_menu_item_new_with_label("Save State");
	loadstate = gtk_menu_item_new_with_label("Load State");
	cheats = gtk_menu_item_new_with_label("Cheats");
	
	configuration = gtk_menu_item_new_with_label("Configuration");
	videoconfig = gtk_menu_item_new_with_label("Video");
	audioconfig = gtk_menu_item_new_with_label("Audio");
	inputconfig = gtk_menu_item_new_with_label("Input");
	miscconfig = gtk_menu_item_new_with_label("Misc");
  
	help = gtk_menu_item_new_with_label("Help");
	about = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, NULL);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(emulator), emulatormenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), run);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), pause);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), savestate);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), loadstate);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), cheats);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(configuration), configurationmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(configurationmenu), videoconfig);
	gtk_menu_shell_append(GTK_MENU_SHELL(configurationmenu), audioconfig);
	gtk_menu_shell_append(GTK_MENU_SHELL(configurationmenu), inputconfig);
	gtk_menu_shell_append(GTK_MENU_SHELL(configurationmenu), miscconfig);
  
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);
  
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), emulator);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), configuration);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);
	
	drawingarea = gtk_drawing_area_new();
	gtk_widget_set_size_request (drawingarea, 200, 200);
	
	statusbar = gtk_statusbar_new();
	
	gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), drawingarea, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), statusbar, FALSE, FALSE, 0);

	g_signal_connect_swapped(G_OBJECT(window), "destroy",
		G_CALLBACK(on_mainwindow_destroy), NULL);

	g_signal_connect(G_OBJECT(open), "activate",
		G_CALLBACK(on_open_clicked), NULL);
		
	g_signal_connect(G_OBJECT(quit), "activate",
		G_CALLBACK(on_mainwindow_destroy), NULL);

	g_signal_connect(G_OBJECT(run), "activate",
		G_CALLBACK(on_playbutton_clicked), NULL);
		
	g_signal_connect(G_OBJECT(savestate), "activate",
		G_CALLBACK(state_save), NULL);

	g_signal_connect(G_OBJECT(loadstate), "activate",
		G_CALLBACK(state_load), NULL);

	g_signal_connect(G_OBJECT(cheats), "activate",
		G_CALLBACK(on_cheatbutton_pressed), NULL);

	g_signal_connect(G_OBJECT(videoconfig), "activate",
		G_CALLBACK(create_videoconfig), NULL);
	
	g_signal_connect(G_OBJECT(audioconfig), "activate",
		G_CALLBACK(create_audioconfig), NULL);
		
	g_signal_connect(G_OBJECT(inputconfig), "activate",
		G_CALLBACK(create_inputconfig), NULL);
		
	g_signal_connect(G_OBJECT(miscconfig), "activate",
		G_CALLBACK(create_miscconfig), NULL);
        
	g_signal_connect(G_OBJECT(about), "activate",
		G_CALLBACK(create_about), NULL);

	gtk_widget_show_all(window);

	return window;
}

void videoconfig_clicked() {
	create_videoconfig();
}

void audioconfig_clicked() {
	create_audioconfig();
}

void inputconfig_clicked() {
	create_inputconfig();
}

void miscconfig_clicked() {
	create_miscconfig();
}

void about_clicked() {
	create_about();
}

GtkWidget* create_inputconfig (void) {
	printf("Input Dialog\n");
	return 0;
}

//The Old

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    g_object_ref (widget), (GDestroyNotify) g_object_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

/*GtkWidget*
create_mainwindow (void)
{
  GtkWidget *mainwindow;
  AtkObject *atko;
  GtkWidget *notebook1;
  GtkWidget *fixed1;
  GObject *nsfspinbutton_adj;
  GtkWidget *nsfspinbutton;
  GtkWidget *nsfmaker;
  GtkWidget *nsfauthor;
  GtkWidget *nsftitle;
  GtkWidget *open;
  GtkWidget *playbutton;
  GtkWidget *nsfstop;
  GtkWidget *nsfplay;
  GtkWidget *cheatbutton;
  GtkWidget *label1;
  GtkWidget *fixed2;
  GtkWidget *scaleamtcombo;
  GtkWidget *label16;
  GtkWidget *label8;
  GtkWidget *scalecombo;
  GtkWidget *check_fullscreen;
  GtkWidget *unlimitsprcheck;
  GtkWidget *videocombo;
  GtkWidget *label11;
  GtkWidget *label17;
  GtkWidget *label10;
  GtkWidget *ntsccombo;
  GtkWidget *rendercombo;
  GtkWidget *label9;
  GtkWidget *label2;
  GtkWidget *fixed3;
  GtkWidget *controlcheck;
  GtkWidget *configbutton;
  GtkWidget *configlabel;
  GtkWidget *configcombo;
  GtkWidget *label3;
  GtkWidget *fixed4;
  GtkWidget *label15;
  GtkWidget *label14;
  GtkWidget *volumelabel;
  GtkWidget *volumescroll;
  GtkWidget *surrscroll;
  GtkWidget *surroundlabel;
  GtkWidget *surrcheck;
  GtkWidget *excitecheck;
  GtkWidget *stereocheck;
  GtkWidget *ratecombo;
  GtkWidget *sndapicombo;
  GtkWidget *label4;
  GtkWidget *fixed7;
  GtkWidget *label12;
  GtkWidget *label13;
  GtkWidget *label23;
  GtkWidget *favorcombo;
  GtkWidget *spatchcombo;
  GtkWidget *aboutbutton;
  GtkWidget *misctab;

  mainwindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (mainwindow), _("Nestopia Undead"));

  notebook1 = gtk_notebook_new ();
  gtk_widget_show (notebook1);
  gtk_container_add (GTK_CONTAINER (mainwindow), notebook1);

  fixed1 = gtk_fixed_new ();
  gtk_widget_show (fixed1);
  gtk_container_add (GTK_CONTAINER (notebook1), fixed1);

  nsfspinbutton_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 10);
  nsfspinbutton = gtk_spin_button_new (GTK_ADJUSTMENT (nsfspinbutton_adj), 1, 0);
  gtk_widget_show (nsfspinbutton);
  gtk_fixed_put (GTK_FIXED (fixed1), nsfspinbutton, 408, 104);
  gtk_widget_set_size_request (nsfspinbutton, 72, 35);

  nsfmaker = gtk_label_new ("");
  gtk_widget_show (nsfmaker);
  gtk_fixed_put (GTK_FIXED (fixed1), nsfmaker, 144, 64);
  gtk_widget_set_size_request (nsfmaker, 320, 24);

  nsfauthor = gtk_label_new ("");
  gtk_widget_show (nsfauthor);
  gtk_fixed_put (GTK_FIXED (fixed1), nsfauthor, 144, 32);
  gtk_widget_set_size_request (nsfauthor, 320, 24);
  gtk_label_set_justify (GTK_LABEL (nsfauthor), GTK_JUSTIFY_CENTER);

  nsftitle = gtk_label_new ("");
  gtk_widget_show (nsftitle);
  gtk_fixed_put (GTK_FIXED (fixed1), nsftitle, 144, 0);
  gtk_widget_set_size_request (nsftitle, 320, 24);
  gtk_label_set_justify (GTK_LABEL (nsftitle), GTK_JUSTIFY_CENTER);

  open = gtk_button_new_from_stock ("gtk-open");
  gtk_widget_show (open);
  gtk_fixed_put (GTK_FIXED (fixed1), open, 8, 8);
  gtk_widget_set_size_request (open, 120, 40);

  playbutton = gtk_button_new_with_mnemonic (_("Play Game!"));
  gtk_widget_show (playbutton);
  gtk_fixed_put (GTK_FIXED (fixed1), playbutton, 8, 56);
  gtk_widget_set_size_request (playbutton, 120, 40);

  nsfstop = gtk_button_new_from_stock ("gtk-media-stop");
  gtk_widget_show (nsfstop);
  gtk_fixed_put (GTK_FIXED (fixed1), nsfstop, 192, 104);
  gtk_widget_set_size_request (nsfstop, 96, 32);

  nsfplay = gtk_button_new_from_stock ("gtk-media-play");
  gtk_widget_show (nsfplay);
  gtk_fixed_put (GTK_FIXED (fixed1), nsfplay, 296, 104);
  gtk_widget_set_size_request (nsfplay, 88, 32);

  cheatbutton = gtk_button_new_with_mnemonic (_("Cheats..."));
  gtk_widget_show (cheatbutton);
  gtk_fixed_put (GTK_FIXED (fixed1), cheatbutton, 8, 104);
  gtk_widget_set_size_request (cheatbutton, 120, 40);

  label1 = gtk_label_new (_("Emulator"));
  gtk_widget_show (label1);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 0), label1);

  fixed2 = gtk_fixed_new ();
  gtk_widget_show (fixed2);
  gtk_container_add (GTK_CONTAINER (notebook1), fixed2);

  scaleamtcombo = gtk_combo_box_text_new ();
  gtk_widget_show (scaleamtcombo);
  gtk_fixed_put (GTK_FIXED (fixed2), scaleamtcombo, 64, 56);
  gtk_widget_set_size_request (scaleamtcombo, 80, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (scaleamtcombo), _("1x"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (scaleamtcombo), _("2x"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (scaleamtcombo), _("3x"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (scaleamtcombo), _("4x"));

  label16 = gtk_label_new (_("Scale"));
  gtk_widget_show (label16);
  gtk_fixed_put (GTK_FIXED (fixed2), label16, 8, 64);
  gtk_widget_set_size_request (label16, 47, 17);

  label8 = gtk_label_new (_("Filter"));
  gtk_widget_show (label8);
  gtk_fixed_put (GTK_FIXED (fixed2), label8, 0, 16);
  gtk_widget_set_size_request (label8, 64, 24);

  scalecombo = gtk_combo_box_text_new ();
  gtk_widget_show (scalecombo);
  gtk_fixed_put (GTK_FIXED (fixed2), scalecombo, 64, 8);
  gtk_widget_set_size_request (scalecombo, 152, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (scalecombo), _("None"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (scalecombo), _("NTSC"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (scalecombo), _("Scale?x"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (scalecombo), _("hq?x"));

  check_fullscreen = gtk_check_button_new_with_mnemonic (_("Fullscreen"));
  gtk_widget_show (check_fullscreen);
  gtk_fixed_put (GTK_FIXED (fixed2), check_fullscreen, 8, 96);
  gtk_widget_set_size_request (check_fullscreen, 96, 24);

  unlimitsprcheck = gtk_check_button_new_with_mnemonic (_("Unlimited sprites"));
  gtk_widget_show (unlimitsprcheck);
  gtk_fixed_put (GTK_FIXED (fixed2), unlimitsprcheck, 8, 120);
  gtk_widget_set_size_request (unlimitsprcheck, 128, 24);

  videocombo = gtk_combo_box_text_new ();
  gtk_widget_show (videocombo);
  gtk_fixed_put (GTK_FIXED (fixed2), videocombo, 344, 104);
  gtk_widget_set_size_request (videocombo, 136, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (videocombo), _("Auto"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (videocombo), _("NTSC"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (videocombo), _("PAL"));

  label11 = gtk_label_new (_("Region"));
  gtk_widget_show (label11);
  gtk_fixed_put (GTK_FIXED (fixed2), label11, 280, 104);
  gtk_widget_set_size_request (label11, 56, 32);

  label17 = gtk_label_new (_("type"));
  gtk_widget_show (label17);
  gtk_fixed_put (GTK_FIXED (fixed2), label17, 288, 72);
  gtk_widget_set_size_request (label17, 47, 17);

  label10 = gtk_label_new (_("NTSC"));
  gtk_widget_show (label10);
  gtk_fixed_put (GTK_FIXED (fixed2), label10, 288, 56);
  gtk_widget_set_size_request (label10, 48, 16);

  ntsccombo = gtk_combo_box_text_new ();
  gtk_widget_show (ntsccombo);
  gtk_fixed_put (GTK_FIXED (fixed2), ntsccombo, 344, 56);
  gtk_widget_set_size_request (ntsccombo, 136, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (ntsccombo), _("Composite"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (ntsccombo), _("S-Video"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (ntsccombo), _("RGB"));

  rendercombo = gtk_combo_box_text_new ();
  gtk_widget_show (rendercombo);
  gtk_fixed_put (GTK_FIXED (fixed2), rendercombo, 344, 8);
  gtk_widget_set_size_request (rendercombo, 136, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (rendercombo), _("Soft"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (rendercombo), _("OpenGL"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (rendercombo), _("OpenGL bilinear"));

  label9 = gtk_label_new (_("Renderer"));
  gtk_widget_show (label9);
  gtk_fixed_put (GTK_FIXED (fixed2), label9, 252, 16);
  gtk_widget_set_size_request (label9, 96, 24);

  label2 = gtk_label_new (_("Video"));
  gtk_widget_show (label2);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 1), label2);

  fixed3 = gtk_fixed_new ();
  gtk_widget_show (fixed3);
  gtk_container_add (GTK_CONTAINER (notebook1), fixed3);

  controlcheck = gtk_check_button_new_with_mnemonic (_("Use controllers"));
  gtk_widget_show (controlcheck);
  gtk_fixed_put (GTK_FIXED (fixed3), controlcheck, 8, 16);
  gtk_widget_set_size_request (controlcheck, 136, 24);

  configbutton = gtk_button_new_with_mnemonic (_("Change..."));
  gtk_widget_show (configbutton);
  gtk_fixed_put (GTK_FIXED (fixed3), configbutton, 296, 88);
  gtk_widget_set_size_request (configbutton, 112, 40);

  configlabel = gtk_label_new ("");
  gtk_widget_show (configlabel);
  gtk_fixed_put (GTK_FIXED (fixed3), configlabel, 8, 96);
  gtk_widget_set_size_request (configlabel, 264, 24);

  configcombo = gtk_combo_box_text_new ();
  gtk_widget_show (configcombo);
  gtk_fixed_put (GTK_FIXED (fixed3), configcombo, 8, 48);
  gtk_widget_set_size_request (configcombo, 224, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 1 Up"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 1 Down"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 1 Left"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 1 Right"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 1 A"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 1 B"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 1 START"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 1 SELECT"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 2 Up"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 2 Down"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 2 Left"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 2 Right"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 2 A"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 2 B"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 2 START"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Player 2 SELECT"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Movie Save"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Movie Load"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Movie Stop"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Reset"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Flip FDS Sides"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Save state"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Load state"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Toggle fullscreen"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Stop game"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Stop game and exit NEStopia"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Start rewinder"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Stop rewinder"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Quicksave slot 1"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Quicksave slot 2"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Quickload slot 1"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Quickload slot 2"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Vs. System coin 1"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (configcombo), _("Vs. System coin 2"));

  label3 = gtk_label_new (_("Input"));
  gtk_widget_show (label3);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 2), label3);

  fixed4 = gtk_fixed_new ();
  gtk_widget_show (fixed4);
  gtk_container_add (GTK_CONTAINER (notebook1), fixed4);

  label15 = gtk_label_new (_("Volume:"));
  gtk_widget_show (label15);
  gtk_fixed_put (GTK_FIXED (fixed4), label15, 176, 16);
  gtk_widget_set_size_request (label15, 80, 24);

  label14 = gtk_label_new (_("Output rate:"));
  gtk_widget_show (label14);
  gtk_fixed_put (GTK_FIXED (fixed4), label14, 224, 112);
  gtk_widget_set_size_request (label14, 104, 16);

  volumelabel = gtk_label_new (_("100"));
  gtk_widget_show (volumelabel);
  gtk_fixed_put (GTK_FIXED (fixed4), volumelabel, 440, 16);
  gtk_widget_set_size_request (volumelabel, 40, 24);
  gtk_label_set_justify (GTK_LABEL (volumelabel), GTK_JUSTIFY_CENTER);

  volumescroll = gtk_scrollbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_ADJUSTMENT (gtk_adjustment_new (0, 0, 100, 1, 5, 0)));
  gtk_widget_show (volumescroll);
  gtk_fixed_put (GTK_FIXED (fixed4), volumescroll, 256, 16);
  gtk_widget_set_size_request (volumescroll, 176, 24);

  surrscroll = gtk_scrollbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_ADJUSTMENT (gtk_adjustment_new (0, 0, 100, 1, 5, 0)));
  gtk_widget_show (surrscroll);
  gtk_fixed_put (GTK_FIXED (fixed4), surrscroll, 8, 88);
  gtk_widget_set_size_request (surrscroll, 176, 16);

  surroundlabel = gtk_label_new (_("100"));
  gtk_widget_show (surroundlabel);
  gtk_fixed_put (GTK_FIXED (fixed4), surroundlabel, 128, 64);
  gtk_widget_set_size_request (surroundlabel, 41, 24);

  surrcheck = gtk_check_button_new_with_mnemonic (_("Lite Surround:"));
  gtk_widget_show (surrcheck);
  gtk_fixed_put (GTK_FIXED (fixed4), surrcheck, 8, 64);
  gtk_widget_set_size_request (surrcheck, 128, 24);

  excitecheck = gtk_check_button_new_with_mnemonic (_("Stereo exciter"));
  gtk_widget_show (excitecheck);
  gtk_fixed_put (GTK_FIXED (fixed4), excitecheck, 8, 112);
  gtk_widget_set_size_request (excitecheck, 128, 21);

  stereocheck = gtk_check_button_new_with_mnemonic (_("Stereo"));
  gtk_widget_show (stereocheck);
  gtk_fixed_put (GTK_FIXED (fixed4), stereocheck, 8, 40);
  gtk_widget_set_size_request (stereocheck, 118, 21);

  ratecombo = gtk_combo_box_text_new ();
  gtk_widget_show (ratecombo);
  gtk_fixed_put (GTK_FIXED (fixed4), ratecombo, 328, 104);
  gtk_widget_set_size_request (ratecombo, 144, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (ratecombo), _("11025"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (ratecombo), _("22050"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (ratecombo), _("44100"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (ratecombo), _("48000"));

  sndapicombo = gtk_combo_box_text_new ();
  gtk_widget_show (sndapicombo);
  gtk_fixed_put (GTK_FIXED (fixed4), sndapicombo, 8, 8);
  gtk_widget_set_size_request (sndapicombo, 160, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (sndapicombo), _("SDL"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (sndapicombo), _("ALSA"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (sndapicombo), _("OSS"));
  
  label4 = gtk_label_new (_("Audio"));
  gtk_widget_show (label4);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 3), label4);

  fixed7 = gtk_fixed_new ();
  gtk_widget_show (fixed7);
  gtk_container_add (GTK_CONTAINER (notebook1), fixed7);

  label12 = gtk_label_new (_("Preferred"));
  gtk_widget_show (label12);
  gtk_fixed_put (GTK_FIXED (fixed7), label12, 8, 16);
  gtk_widget_set_size_request (label12, 64, 16);

  label13 = gtk_label_new (_("system"));
  gtk_widget_show (label13);
  gtk_fixed_put (GTK_FIXED (fixed7), label13, 8, 32);
  gtk_widget_set_size_request (label13, 64, 16);

  label23 = gtk_label_new (_("Soft patching"));
  gtk_widget_show (label23);
  gtk_fixed_put (GTK_FIXED (fixed7), label23, 8, 88);
  gtk_widget_set_size_request (label23, 104, 16);

  favorcombo = gtk_combo_box_text_new ();
  gtk_widget_show (favorcombo);
  gtk_fixed_put (GTK_FIXED (fixed7), favorcombo, 88, 16);
  gtk_widget_set_size_request (favorcombo, 128, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (favorcombo), _("NES (NTSC)"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (favorcombo), _("NES (PAL)"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (favorcombo), _("Famicom"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (favorcombo), _("Dendy"));

  spatchcombo = gtk_combo_box_text_new ();
  gtk_widget_show (spatchcombo);
  gtk_fixed_put (GTK_FIXED (fixed7), spatchcombo, 120, 80);
  gtk_widget_set_size_request (spatchcombo, 128, 32);
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (spatchcombo), _("Off"));
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (spatchcombo), _("On"));
  
  aboutbutton = gtk_button_new_from_stock ("gtk-about");
  gtk_widget_show (aboutbutton);
  gtk_fixed_put (GTK_FIXED (fixed7), aboutbutton, 340, 16);
  gtk_widget_set_size_request (aboutbutton, 100, 40);

  misctab = gtk_label_new (_("Extras"));
  gtk_widget_show (misctab);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 4), misctab);

  g_signal_connect ((gpointer) mainwindow, "destroy",
                    G_CALLBACK (on_mainwindow_destroy),
                    NULL);
  g_signal_connect ((gpointer) nsfspinbutton, "change_value",
                    G_CALLBACK (on_nsfspinbutton_change_value),
                    NULL);
  g_signal_connect ((gpointer) nsfspinbutton, "value_changed",
                    G_CALLBACK (on_nsfspinbutton_value_changed),
                    NULL);
  g_signal_connect ((gpointer) open, "clicked",
                    G_CALLBACK (on_open_clicked),
                    NULL);
  g_signal_connect ((gpointer) playbutton, "clicked",
                    G_CALLBACK (on_playbutton_clicked),
                    NULL);
  g_signal_connect ((gpointer) nsfstop, "clicked",
                    G_CALLBACK (on_nsfstop_clicked),
                    NULL);
  g_signal_connect ((gpointer) nsfplay, "clicked",
                    G_CALLBACK (on_nsfplay_clicked),
                    NULL);
  g_signal_connect ((gpointer) cheatbutton, "pressed",
                    G_CALLBACK (on_cheatbutton_pressed),
                    NULL);
  g_signal_connect ((gpointer) aboutbutton, "clicked",
                    G_CALLBACK (on_aboutbutton_clicked),
                    NULL);
  g_signal_connect ((gpointer) scaleamtcombo, "changed",
                    G_CALLBACK (on_scaleamtcombo_changed),
                    NULL);
  g_signal_connect ((gpointer) scalecombo, "changed",
                    G_CALLBACK (on_scalecombo_changed),
                    NULL);
  g_signal_connect ((gpointer) check_fullscreen, "toggled",
                    G_CALLBACK (on_check_fullscreen_toggled),
                    NULL);
  g_signal_connect ((gpointer) unlimitsprcheck, "toggled",
                    G_CALLBACK (on_unlimitsprcheck_toggled),
                    NULL);
  g_signal_connect ((gpointer) videocombo, "changed",
                    G_CALLBACK (on_videocombo_changed),
                    NULL);
  g_signal_connect ((gpointer) ntsccombo, "changed",
                    G_CALLBACK (on_ntsccombo_changed),
                    NULL);
  g_signal_connect ((gpointer) rendercombo, "changed",
                    G_CALLBACK (on_rendercombo_changed),
                    NULL);
  g_signal_connect ((gpointer) controlcheck, "toggled",
                    G_CALLBACK (on_controlcheck_toggled),
                    NULL);
  g_signal_connect ((gpointer) configbutton, "clicked",
                    G_CALLBACK (on_configbutton_clicked),
                    NULL);
  g_signal_connect ((gpointer) configcombo, "changed",
                    G_CALLBACK (on_configcombo_changed),
                    NULL);
  g_signal_connect ((gpointer) volumescroll, "value_changed",
                    G_CALLBACK (on_volumescroll_value_changed),
                    NULL);
  g_signal_connect ((gpointer) volumescroll, "configure_event",
                    G_CALLBACK (on_volumescroll_configure_event),
                    NULL);
  g_signal_connect ((gpointer) surrscroll, "value_changed",
                    G_CALLBACK (on_surrscroll_value_changed),
                    NULL);
  g_signal_connect ((gpointer) surrcheck, "toggled",
                    G_CALLBACK (on_surrcheck_toggled),
                    NULL);
  g_signal_connect ((gpointer) excitecheck, "toggled",
                    G_CALLBACK (on_excitecheck_toggled),
                    NULL);
  g_signal_connect ((gpointer) stereocheck, "toggled",
                    G_CALLBACK (on_stereocheck_toggled),
                    NULL);
  g_signal_connect ((gpointer) ratecombo, "changed",
                    G_CALLBACK (on_ratecombo_changed),
                    NULL);
  g_signal_connect ((gpointer) ratecombo, "configure_event",
                    G_CALLBACK (on_ratecombo_configure_event),
                    NULL);
  g_signal_connect ((gpointer) sndapicombo, "changed",
                    G_CALLBACK (on_sndapicombo_changed),
                    NULL);
  g_signal_connect ((gpointer) favorcombo, "changed",
                    G_CALLBACK (on_favorcombo_changed),
                    NULL);
  g_signal_connect ((gpointer) spatchcombo, "changed",
                    G_CALLBACK (on_spatchcombo_changed),
                    NULL);

  atko = gtk_widget_get_accessible (mainwindow);
  atk_object_set_description (atko, _("Nintendo Entertainment System emulator controls"));


  // Store pointers to all widgets, for use by lookup_widget().
  GLADE_HOOKUP_OBJECT_NO_REF (mainwindow, mainwindow, "mainwindow");
  GLADE_HOOKUP_OBJECT (mainwindow, notebook1, "notebook1");
  GLADE_HOOKUP_OBJECT (mainwindow, fixed1, "fixed1");
  GLADE_HOOKUP_OBJECT (mainwindow, nsfspinbutton, "nsfspinbutton");
  GLADE_HOOKUP_OBJECT (mainwindow, nsfmaker, "nsfmaker");
  GLADE_HOOKUP_OBJECT (mainwindow, nsfauthor, "nsfauthor");
  GLADE_HOOKUP_OBJECT (mainwindow, nsftitle, "nsftitle");
  GLADE_HOOKUP_OBJECT (mainwindow, open, "open");
  GLADE_HOOKUP_OBJECT (mainwindow, playbutton, "playbutton");
  GLADE_HOOKUP_OBJECT (mainwindow, nsfstop, "nsfstop");
  GLADE_HOOKUP_OBJECT (mainwindow, nsfplay, "nsfplay");
  GLADE_HOOKUP_OBJECT (mainwindow, cheatbutton, "cheatbutton");
  GLADE_HOOKUP_OBJECT (mainwindow, label1, "label1");
  GLADE_HOOKUP_OBJECT (mainwindow, fixed2, "fixed2");
  GLADE_HOOKUP_OBJECT (mainwindow, scaleamtcombo, "scaleamtcombo");
  GLADE_HOOKUP_OBJECT (mainwindow, label16, "label16");
  GLADE_HOOKUP_OBJECT (mainwindow, label8, "label8");
  GLADE_HOOKUP_OBJECT (mainwindow, scalecombo, "scalecombo");
  GLADE_HOOKUP_OBJECT (mainwindow, check_fullscreen, "check_fullscreen");
  GLADE_HOOKUP_OBJECT (mainwindow, unlimitsprcheck, "unlimitsprcheck");
  GLADE_HOOKUP_OBJECT (mainwindow, videocombo, "videocombo");
  GLADE_HOOKUP_OBJECT (mainwindow, label11, "label11");
  GLADE_HOOKUP_OBJECT (mainwindow, label17, "label17");
  GLADE_HOOKUP_OBJECT (mainwindow, label10, "label10");
  GLADE_HOOKUP_OBJECT (mainwindow, ntsccombo, "ntsccombo");
  GLADE_HOOKUP_OBJECT (mainwindow, rendercombo, "rendercombo");
  GLADE_HOOKUP_OBJECT (mainwindow, label9, "label9");
  GLADE_HOOKUP_OBJECT (mainwindow, label2, "label2");
  GLADE_HOOKUP_OBJECT (mainwindow, fixed3, "fixed3");
  GLADE_HOOKUP_OBJECT (mainwindow, controlcheck, "controlcheck");
  GLADE_HOOKUP_OBJECT (mainwindow, configbutton, "configbutton");
  GLADE_HOOKUP_OBJECT (mainwindow, configlabel, "configlabel");
  GLADE_HOOKUP_OBJECT (mainwindow, configcombo, "configcombo");
  GLADE_HOOKUP_OBJECT (mainwindow, label3, "label3");
  GLADE_HOOKUP_OBJECT (mainwindow, fixed4, "fixed4");
  GLADE_HOOKUP_OBJECT (mainwindow, label15, "label15");
  GLADE_HOOKUP_OBJECT (mainwindow, label14, "label14");
  GLADE_HOOKUP_OBJECT (mainwindow, volumelabel, "volumelabel");
  GLADE_HOOKUP_OBJECT (mainwindow, volumescroll, "volumescroll");
  GLADE_HOOKUP_OBJECT (mainwindow, surrscroll, "surrscroll");
  GLADE_HOOKUP_OBJECT (mainwindow, surroundlabel, "surroundlabel");
  GLADE_HOOKUP_OBJECT (mainwindow, surrcheck, "surrcheck");
  GLADE_HOOKUP_OBJECT (mainwindow, excitecheck, "excitecheck");
  GLADE_HOOKUP_OBJECT (mainwindow, stereocheck, "stereocheck");
  GLADE_HOOKUP_OBJECT (mainwindow, ratecombo, "ratecombo");
  GLADE_HOOKUP_OBJECT (mainwindow, sndapicombo, "sndapicombo");
  GLADE_HOOKUP_OBJECT (mainwindow, label4, "label4");
  GLADE_HOOKUP_OBJECT (mainwindow, fixed7, "fixed7");
  GLADE_HOOKUP_OBJECT (mainwindow, label12, "label12");
  GLADE_HOOKUP_OBJECT (mainwindow, label13, "label13");
  GLADE_HOOKUP_OBJECT (mainwindow, label23, "label23");
  GLADE_HOOKUP_OBJECT (mainwindow, favorcombo, "favorcombo");
  GLADE_HOOKUP_OBJECT (mainwindow, spatchcombo, "spatchcombo");
  GLADE_HOOKUP_OBJECT (mainwindow, aboutbutton, "aboutbutton");
  GLADE_HOOKUP_OBJECT (mainwindow, misctab, "misctab");

  return mainwindow;
}*/

GtkWidget* create_archselect (void) {

	GtkWidget *archselect;
	GtkWidget *fixed5;
	GtkWidget *scrolledwindow1;
	GtkWidget *archtree;
	GtkWidget *label18;
	GtkWidget *label19;
	GtkWidget *archcancel;
	GtkWidget *archok;

	archselect = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (archselect), "Pick game in archive");
	gtk_window_set_modal (GTK_WINDOW (archselect), TRUE);

	fixed5 = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (archselect), fixed5);

	archtree = gtk_tree_view_new ();
	gtk_container_add (GTK_CONTAINER (scrolledwindow1), archtree);
	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (archtree), FALSE);

	scrolledwindow1 = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put (GTK_FIXED (fixed5), scrolledwindow1, 0, 0);
	gtk_widget_set_size_request (scrolledwindow1, 336, 352);

	label18 = gtk_label_new ("Choose an NES cartridge,");
	gtk_fixed_put (GTK_FIXED (fixed5), label18, 344, 8);
	gtk_widget_set_size_request (label18, 176, 24);

	label19 = gtk_label_new ("disc, or music file.");
	gtk_fixed_put (GTK_FIXED (fixed5), label19, 344, 32);
	gtk_widget_set_size_request (label19, 176, 16);

	archcancel = gtk_button_new_from_stock ("gtk-cancel");
	gtk_fixed_put (GTK_FIXED (fixed5), archcancel, 344, 304);
	gtk_widget_set_size_request (archcancel, 168, 40);

	archok = gtk_button_new_from_stock ("gtk-ok");
	gtk_fixed_put (GTK_FIXED (fixed5), archok, 344, 248);
	gtk_widget_set_size_request (archok, 168, 40);

	g_signal_connect (G_OBJECT(archcancel), "clicked",
		G_CALLBACK (on_archcancel_clicked), NULL);

	g_signal_connect (G_OBJECT(archok), "clicked",
		G_CALLBACK (on_archok_clicked), NULL);
		
	GLADE_HOOKUP_OBJECT_NO_REF (archselect, archselect, "archselect");
	GLADE_HOOKUP_OBJECT (archselect, fixed5, "fixed5");
	GLADE_HOOKUP_OBJECT (archselect, scrolledwindow1, "scrolledwindow1");
	GLADE_HOOKUP_OBJECT (archselect, archtree, "archtree");
	GLADE_HOOKUP_OBJECT (archselect, label18, "label18");
	GLADE_HOOKUP_OBJECT (archselect, label19, "label19");
	GLADE_HOOKUP_OBJECT (archselect, archcancel, "archcancel");
	GLADE_HOOKUP_OBJECT (archselect, archok, "archok");

	gtk_widget_show_all(archselect);

	return archselect;
}

GtkWidget* create_about (void) {

	char svgpath[1024];
	sprintf(svgpath, "%s/icons/nestopia.svg", DATADIR);
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(svgpath, 256, 256, NULL);
	
	GtkWidget *aboutdialog = gtk_about_dialog_new();
	
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(aboutdialog), pixbuf);
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(aboutdialog), "Nestopia Undead");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(aboutdialog), "1.43");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(aboutdialog), "An accurate Nintendo Entertainment System Emulator");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(aboutdialog), "http://0ldsk00l.ca/");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(aboutdialog), "(c) 2012, R. Danbrook\n(c) 2007-2008, R. Belmont\n(c) 2003-2008, Martin Freij\n\nIcon based on art from Trollekop");
	g_object_unref(pixbuf), pixbuf = NULL;
	gtk_dialog_run(GTK_DIALOG(aboutdialog));
	gtk_widget_destroy(aboutdialog);
	
	return aboutdialog;
}
