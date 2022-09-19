# Shopify App Template - C

This is a template for building a [Shopify app](https://shopify.dev/apps/getting-started) using C. It contains the basics for building a Shopify app.

## Benefits

The C app template comes with the following out-of-the-box functionality:

- OAuth: Installing the app and granting permissions

## Tech Stack

This template combines a number of third party open-source tools:

- [libmicrohttpd](https://gnu.org/software/libmicrohttpd/) builds the backend.

The following tool complements to ease app development:

- [libshopify](http://darapsa.org/?p=libshopify.git) adds OAuth to the libmicrohttpd backend. This lets users install the app and grant scope permissions.

## Getting started

### Requirements

1. You must [create a Shopify partner account](https://partners.shopify.com/signup) if you don’t have one.
2. You must [create a development store](https://help.shopify.com/en/partners/dashboard/development-stores#create-a-development-store) if you don’t have one.

## Deployment

### Build

The frontend is a single page.

You need to build the backend.

```shell
export CPPFLAGS="$CPPFLAGS -DAPP_URL=\\\"https://your.public/host\\\" -DAPP_ID=\\\"yourapp\\\" -DAPI_KEY=\\\"0123456789abcedf\\\" -API_SECRET_KEY=\\\"vwxyz_0123456789abcdef\\\" -DAPP_DIR=\\\"/path/to/your/app/dir\\\""
autoreconf -is
mkdir -p build
cd build
../configure
make
```

## Developer resources

- [App authentication](https://shopify.dev/apps/auth)
