#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <mpg123.h>
#include <ao/ao.h>
#include <glib.h>

struct MemoryStruct {
	char *memory;
	size_t size;
};

mpg123_handle *mh;
ao_device *dev;

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Music App");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);

  gtk_widget_show_all(window);

}

void play_mp3(const char *filename) {

	unsigned char *buffer;
	size_t buffer_size;
	size_t done;
	int err;
	ao_initialize();
	mpg123_init();
	int driver = ao_default_driver_id();
	mh = mpg123_new(NULL, NULL);

	err = mpg123_open(mh, filename);
	if(err!= MPG123_OK) {
		printf("Couldn't open mp3 file error!");
	}
	buffer_size = mpg123_outblock(mh);
	buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));
	int channels, encoding;
	long rate;
	mpg123_getformat(mh, &rate, &channels, &encoding);
	ao_sample_format format = {16, rate, channels, AO_FMT_NATIVE, NULL};
	dev = ao_open_live(driver, &format, NULL);

	while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
		ao_play(dev, buffer, buffer_size);
	//	printf("test");
	}
	mpg123_close(mh);
	ao_close(dev);
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if (!ptr) {
    printf("Not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

struct MemoryStruct chunk;

int
main (int    argc,
      char **argv)
{

 int status;
      
  GtkApplication *app;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

  play_mp3("euphoria.mp3");

  status = g_application_run (G_APPLICATION (app), argc, argv);

  g_object_unref (app);

  return status;
}


