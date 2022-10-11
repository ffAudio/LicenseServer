

#pragma once

namespace licensing
{

namespace Data
{

//! This is the server to connect to to fetch licenses
extern const char* server;

//! This is the website to launch in the browser if the user wants to buy a license
extern const char* productPage;

//! This is a identifier to select the key to talk to the server. It is unique as pair of product / version
extern const char* productUuid;

//! The public key to encrypt and decrypt license data
extern const char* publicKey;

//! The hash to verify the public key
extern long        hash;

//! define if popup may be closed
extern bool        closingPopupAllowed;

} // namespace Data

} // namespace licensing
