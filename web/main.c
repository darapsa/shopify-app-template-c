#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <shopify.h>

static enum MHD_Result handle_request(void *cls, struct MHD_Connection *conn,
		const char *url, const char *method, const char *version,
		const char *upload_data, size_t *upload_data_size,
		void **con_cls)
{
	if (strcmp(method, "GET"))
		return MHD_NO;
	struct shopify_param *params = *con_cls;
	if (!params) {
		params = malloc(sizeof(struct shopify_param));
		*con_cls = params;
		return MHD_YES;
	}
	static const char *redir_url = "/auth";
	if (!shopify_valid(conn, url, redir_url, API_SECRET_KEY, &params)) {
		free(params);
		return MHD_NO;
	}
	const size_t dir_len = strlen(APP_DIR);
	static const char *toml_rel_path = "/shopify.app.toml";
	char toml_abs_path[dir_len + strlen(toml_rel_path) + 1];
	sprintf(toml_abs_path, "%s%s", APP_DIR, toml_rel_path);
	static const char *html_rel_path = "/web/frontend/index.html";
	char html_abs_path[dir_len + strlen(html_rel_path) + 1];
	sprintf(html_abs_path, "%s%s", APP_DIR, html_rel_path);
	struct MHD_Response *resp;
	enum MHD_Result ret = shopify_respond(params, url, redir_url, APP_URL,
			APP_ID, API_KEY, API_SECRET_KEY, toml_abs_path,
			html_abs_path, conn, &resp);
	MHD_destroy_response(resp);
	free(params);
	return ret;
}

int main(int argc, char *argv[])
{
	shopify_init();
	struct MHD_Daemon *daemon
		= MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, 3000, NULL,
				NULL, &handle_request, NULL, MHD_OPTION_END);
	getchar();
	MHD_stop_daemon(daemon);
	shopify_cleanup();
	return 0;
}
