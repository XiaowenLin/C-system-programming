/* make deps */
void make_deps(queue_t *deps);
void make_deps(queue_t *deps){
    int i;
    char *dep;
    for (i = 0; i < queue_size(deps); i++){
        dep = queue_at(deps, i);
        make_helper(dep);
    }
    return;
}



    /* make */
    /*int i;
    rule_t *tmp;
    for (i = 0; i < queue_size(&rules); i++){
        tmp = (rule_t *)queue_at(&rules, i);
        puts(tmp->target);
        make_helper(tmp->target);
    }*/
void make_helper(void *t){
    /* block all others */
    pthread_mutex_lock(&makemutex);
    printf("thread %d get lock\n", gettid());
    /* aquire a target to make */
    rule_t *rule = queue_at(head, num_running);
    printf("thread %d get rule at %d and update num_running to %d \n", gettid(), num_running, num_running + 1);
    num_running++;
    /* wait until runnable */
    queue_t deps;
    queue_init(&deps);
    deps_in_rule(rule, &deps);
    while (){
        
        printf("rule runnable\n");
    }
    if (queue_size(&deps) != 0){
        printf("queue_size %d\n", queue_size(&deps));
        make_deps(&deps);
    }
    int exist = access(target, R_OK);
    if (exist != 0 || rule_outdated(rule)){
         printf("%s\n", target);
         run_cmd(rule->commands);
    }else{
        puts("[ready]");
    }
    /* release mutex */
    pthread_mutex_unlock(&makemutex);
    queue_destroy(&deps);
}
