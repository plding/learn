
void ngx_time_init()
{
    struct timeval  tv;

    ngx_memzero(&ngx_cached_gmtime, sizeof(ngx_tm_t));
#ifdef ngx_tm_zone
    ngx_cached_gmtime.ngx_tm_zone = "GMT";
#endif

    ngx_cached_err_log_time.len = sizeof("1970/09/28 12:00:00") - 1;

    ngx_gettimeofday(&tv);

    ngx_time_update(tv.tv_sec);
}


void ngx_time_update(time_t s)
{
    u_char     *p;
    ngx_tm_t    tm;

    if (ngx_time() == s) {
        return;
    }
}
