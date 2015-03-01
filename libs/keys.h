/**
* File "keys.h"
* Created by Sina on Sun Mar  1 19:01:44 2015.
*/

#pragma once

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include "Header.h"

class KeyPair{
public:
    string pub;
    string priv;
    KeyPair(string Pub, string Priv): pub(Pub), priv(Priv) {}
};

KeyPair getKeyPair(int);
