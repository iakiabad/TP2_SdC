//adaptado de ejemplo de la página de libcurl: getinmemory.c - https://curl.se/libcurl/c/getinmemory.html
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <curl/curl.h>
 
struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t write_cb(char *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&mem->memory[mem->size], contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
int main(void)
{
  CURL *curl;
  CURLcode result;
 
  struct MemoryStruct chunk;
 
  result = curl_global_init(CURL_GLOBAL_ALL);
  if(result != CURLE_OK)
    return (int)result;
 
  chunk.memory = malloc(1); /* grown as needed by the realloc above */
  chunk.size = 0;           /* no data at this point */
 
  /* init the curl session */
  curl = curl_easy_init();
  if(curl) {
 
    /* specify URL to get */
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.worldbank.org/v2/en/country/all/indicator/SI.POV.GINI?format=json&date=2011:2020&per_page=32500&page=1&country=%22Argentina%22");
 
    /* send all data to this function */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
 
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
 
    /* some servers do not like requests that are made without a user-agent
       field, so we provide one */
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
    /* get it! */
    result = curl_easy_perform(curl);
 
    /* check for errors */
    if(result != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(result));
    }
    else {
      /*
       * Now, our chunk.memory points to a memory block that is chunk.size
       * bytes big and contains the remote file.
       *
       * Do something nice with it!
       */
      char *ptr_dato = strstr(chunk.memory, "\"ARG\",\"date\":\"2014\",\"value\":");
      ptr_dato += strlen("\"ARG\",\"date\":\"2014\",\"value\":");
      float dato = strtof(ptr_dato, NULL);

      printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
      printf("El índice de GINI de Argentina en 2014 fue de: %f\n", dato);
    }
 
    /* cleanup curl stuff */
    curl_easy_cleanup(curl);
  }
 
  free(chunk.memory);
 
  /* we are done with libcurl, so clean it up */
  curl_global_cleanup();
 
  return (int)result;
}