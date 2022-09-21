#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <shopify.h>

static char *html(const char *host)
{
	static const char *path_rel = "/frontend/index.html";
	char path[strlen(APP_DIR) + strlen(path_rel) + 1];
	sprintf(path, "%s%s", APP_DIR, path_rel);
	int fd = open(path, O_RDONLY);
	struct stat sb;
	fstat(fd, &sb);
	char template[sb.st_size + 1];
	read(fd, path, sb.st_size);
	close(fd);
	const size_t html_len = sb.st_size - strlen("%s") * 4 + strlen(API_KEY)
		+ strlen(host) + strlen(APP_URL) * 2;
	char *html = malloc(html_len + 1);
	sprintf(html, template, API_KEY, host, APP_URL, APP_URL);
	return html;
}

int main(int argc, char *argv[])
{
	const size_t app_dir_len = strlen(APP_DIR);
	static const char *scopes_rel = "/shopify.app.toml";
	char scopes[app_dir_len + strlen(scopes_rel) + 1];
	sprintf(scopes, "%s%s", APP_DIR, scopes_rel);
	static const char *js_dir_rel = "/frontend/build";
	char js_dir[app_dir_len + strlen(js_dir_rel) + 1];
	sprintf(js_dir, "%s%s", APP_DIR, js_dir_rel);
	shopify_app(API_KEY, API_SECRET_KEY, APP_URL, "/auth", APP_ID, scopes,
			html, js_dir, (struct shopify_api[]){
			{
				"/products",
				"GET",
				shopify_graphql,
				"{"\
				"  productCreate() {"\
				"    product {"\
				"      id"\
				"    }"\
				"  }"\
				"}"
			},
			{}
		}
	);
	return 0;
}
