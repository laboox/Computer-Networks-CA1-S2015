/**
* File "keys.cpp"
* Created by Sina on Sun Mar  1 19:01:40 2015.
*/

#include "keys.h"

class EncryptionException: public exception {} EncryptionEx;
class DecryptionException: public exception {} DecryptionEx;
class RSACreateException: public exception {} RSACreateEx;

int padding = RSA_PKCS1_PADDING;

KeyPair getKeyPair(int length){
    size_t pri_len;            // Length of private key
    size_t pub_len;            // Length of public key
    char   *pri_key;           // Private key
    char   *pub_key;           // Public key
    char   *encrypt = NULL;    // Encrypted message
    char   *decrypt = NULL;    // Decrypted message
    char   *err;               // Buffer for any error messages
    BIGNUM* e;
    e = BN_new();
    BN_set_word(e, 65537);
//    RSA *keypair = RSA_generate_key(length, 3, NULL, NULL);
    RSA *keypair;
    if(!RSA_generate_key_ex(keypair, length, e, NULL)){
        cout<<"failed to create key pair!\n";
    }

    BIO *pri = BIO_new(BIO_s_mem());
    BIO *pub = BIO_new(BIO_s_mem());

    PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
    PEM_write_bio_RSAPublicKey(pub, keypair);

    pri_len = BIO_pending(pri);
    pub_len = BIO_pending(pub);

    pri_key = (char*)malloc(pri_len + 1);
    pub_key = (char*)malloc(pub_len + 1);

    BIO_read(pri, pri_key, pri_len);
    BIO_read(pub, pub_key, pub_len);

    pri_key[pri_len] = '\0';
    pub_key[pub_len] = '\0';

    KeyPair kp(pub_key, pri_key);

    RSA_free(keypair);
    BIO_free_all(pub);
    BIO_free_all(pri);
    free(pri_key);
    free(pub_key);
    return kp;
}

RSA * createRSA(const char * key,bool pub) 
{ 
    RSA *rsa= NULL; 
    BIO *keybio ; 
    keybio = BIO_new_mem_buf((void*)key, -1); 
    if (keybio==NULL) 
    { 
        printf( "Failed to create key BIO\n"); 
        return 0; 
    } 
    if(pub) 
    { 
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL); 
    } 
    else 
    { 
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL); 
    } 
    if(rsa == NULL) 
    { 
        printf( "Failed to create RSA\n"); 
    } 

    return rsa;
}

int public_encrypt(unsigned char * data,int data_len,unsigned char * key, unsigned char *encrypted)
{
    RSA * rsa = createRSA((char*)key,1);
    int result = RSA_public_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}

int private_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted)
{
    RSA * rsa = createRSA((char*)key,0);
    int  result = RSA_private_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}
 
int private_encrypt(unsigned char * data,int data_len,const unsigned char * key, unsigned char *encrypted)
{
    RSA * rsa = createRSA((const char*)key,0);
    int result = RSA_private_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}

int private_encrypt(string data, const char * key, unsigned char *encrypted)
{
//    unsigned char dataArr[MAX_MSG_SIZE];
//    memcpy(dataArr, data.c_str(), strlen(data.c_str())+1);
    RSA * rsa = createRSA((char*)key,0);
    int result = RSA_private_encrypt(strlen(data.c_str()),(unsigned char*)data.c_str(),encrypted,rsa,padding);
    return result;
}

int public_decrypt(unsigned char * enc_data,int data_len,const char * key, unsigned char *decrypted)
{
    RSA * rsa = createRSA((char*)key,1);
    int  result = RSA_public_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}

string public_decrypt(unsigned char * enc_data,int data_len,const char * key)
{
    unsigned char dataArr[MAX_MSG_SIZE];
    memset(dataArr, 0 , sizeof(dataArr));
    RSA * rsa = createRSA((char*)key,1);
    int result = public_decrypt(enc_data, data_len, key, dataArr);
    string ret = (char*) dataArr;
    return ret;
}

