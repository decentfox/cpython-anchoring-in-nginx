#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>
#include <ngx_http.h>

static ngx_int_t setup(ngx_conf_t *cf);

static ngx_int_t do_sleep(ngx_http_request_t *r);

static void wake_up(ngx_event_t *e);

static ngx_http_module_t ngx_sleep_module_ctx = {
        NULL,   /* preconfiguration */
        setup,  /* postconfiguration */

        NULL,   /* create main configuration */
        NULL,   /* init main configuration */

        NULL,   /* create server configuration */
        NULL,   /* merge server configuration */

        NULL,   /* create location configuration */
        NULL    /* merge location configuration */
};


ngx_module_t ngx_sleep_module = {
        NGX_MODULE_V1,
        &ngx_sleep_module_ctx,  /* module context */
        NULL,                   /* module commands */
        NGX_HTTP_MODULE,        /* module type */
        NULL,                   /* init master */
        NULL,                   /* init module */
        NULL,                   /* init process */
        NULL,                   /* init thread */
        NULL,                   /* exit thread */
        NULL,                   /* exit process */
        NULL,                   /* exit master */
        NGX_MODULE_V1_PADDING
};


static ngx_int_t setup(ngx_conf_t *cf) {
    ngx_http_handler_pt *h;
    ngx_http_core_main_conf_t *cmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    h = ngx_array_push(&cmcf->phases[NGX_HTTP_POST_READ_PHASE].handlers);
    if (h == NULL) {
        return NGX_ERROR;
    }
    *h = do_sleep;

    return NGX_OK;
}


static ngx_int_t do_sleep(ngx_http_request_t *r) {
    void *ctx = ngx_http_get_module_ctx(r, ngx_sleep_module);
    if (ctx == NULL) {
        ngx_log_error(NGX_LOG_CRIT, r->connection->log, 0, "Before sleep");
        ctx = ngx_calloc(sizeof(ngx_event_t), r->connection->log);
        if (ctx == NULL) return NGX_DECLINED;
        ngx_event_t *sleep_event = (ngx_event_t *) ctx;
        sleep_event->log = r->connection->log;
        sleep_event->data = r;
        sleep_event->handler = wake_up;
        ngx_add_timer(sleep_event, 1000);
        ngx_http_set_ctx(r, ctx, ngx_sleep_module);
        return NGX_AGAIN;
    } else {
        ngx_log_error(NGX_LOG_CRIT, r->connection->log, 0, "After sleep");
        ngx_http_set_ctx(r, NULL, ngx_sleep_module);
        ngx_free(ctx);
        return NGX_DECLINED;
    }
}


static void wake_up(ngx_event_t *e) {
    ngx_http_core_run_phases((ngx_http_request_t *) e->data);
}
