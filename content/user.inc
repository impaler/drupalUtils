<?php

function createUser($settings) {
    
    $account = new stdClass();
    $account->name = $settings[ 'name' ];

    user_save($account);
}

//todo test
function get_user_posts_count($uid,$type = 'your_desired_content_type') {
    $query = db_select('node', 'n');
    $query->condition('uid',$uid,'=');
    $query->condition('type',$type,'=');
    $query->addExpression('COUNT(nid)', 'posts_count');
    $result = $query->execute();

    if ($record = $result->fetchAssoc())
        return $record['posts_count'];
    
    return 0;
}

//todo test
function get_user_comments_count($uid) {
    $query = db_select('comment', 'c');
    $query->condition('uid',$uid,'=');
    $query->addExpression('COUNT(cid)', 'comments_count');
    $result = $query->execute();

    if ($record = $result->fetchAssoc())
        return $record['comments_count'];
    
    return 0;
}