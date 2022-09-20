#include <string.h>
#include <stdio.h>
#include <shopify.h>

int main(int argc, char *argv[])
{
	const size_t app_dir_len = strlen(APP_DIR);
	static const char *scopes_rel = "/shopify.app.toml";
	char scopes[app_dir_len + strlen(scopes_rel) + 1];
	sprintf(scopes, "%s%s", APP_DIR, scopes_rel);
	static const char *index_rel = "/frontend/index.html";
	char index[app_dir_len + strlen(index_rel) + 1];
	sprintf(index, "%s%s", APP_DIR, index_rel);
	shopify_app(API_KEY, API_SECRET_KEY, APP_URL, "/auth", APP_ID, scopes, index,
			(struct shopify_api[]){
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
