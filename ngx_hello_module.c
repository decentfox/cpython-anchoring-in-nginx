#include <ngx_config.h>
#include <ngx_core.h>

static ngx_core_module_t ngx_hello_module_ctx = {
        ngx_string("hello"),
        NULL,
        NULL
};


ngx_int_t hello(ngx_cycle_t *cycle) {
    ngx_log_error(NGX_LOG_CRIT, cycle->log, 0,
                  "Hello, world!");
    return NGX_OK;
}

ngx_module_t ngx_hello_module = {
        NGX_MODULE_V1,
        &ngx_hello_module_ctx,  /* module context */
        NULL,                   /* module commands */
        NGX_CORE_MODULE,        /* module type */
        NULL,                   /* init master */
        hello,                  /* init module */
        NULL,                   /* init process */
        NULL,                   /* init thread */
        NULL,                   /* exit thread */
        NULL,                   /* exit process */
        NULL,                   /* exit master */
        NGX_MODULE_V1_PADDING
};
