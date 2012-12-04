<?php

function createUser ( $settings ) {

    $account = new stdClass;
    
    $account->is_new = TRUE;
    $account->name = $settings[ 'name' ];

    include_once './includes/password.inc';
    $account->pass = user_hash_password ( $settings[ 'pass' ] );
    
    $account->mail = $settings[ 'mail' ];
    $account->init = $settings[ 'mail' ];
    
    $account->status = TRUE;
    
    if ( ! empty ( $settings[ 'roles' ] ) )
        $account->roles = $settings['roles'];
    
    $account->timezone = variable_get ( 'date_default_timezone' , '' );

    $account = user_save ( $account );
    
    //check if there is a picture to add on the filesystem and the account was saved
    if ( isset ($settings['pictureURL']) && $account != FALSE ) {

        $file = saveExistingFileToDB ( $settings['pictureURL'] , $account->uid );
        $edit['picture'] = $file;
        $account = user_save($account, $edit);
    }
    
    return $account;
    

}

function get_user_posts_count ( $uid , $type ) {
    $query = db_select ( 'node' , 'n' );
    $query->condition ( 'uid' , $uid , '=' );
    $query->condition ( 'type' , $type , '=' );
    $query->addExpression ( 'COUNT(nid)' , 'posts_count' );
    $result = $query->execute ();

    if ( $record = $result->fetchAssoc () )
        return $record[ 'posts_count' ];

    return 0;
}

function get_user_comments_count ( $uid ) {
    $query = db_select ( 'comment' , 'c' );
    $query->condition ( 'uid' , $uid , '=' );
    $query->addExpression ( 'COUNT(cid)' , 'comments_count' );
    $result = $query->execute ();

    if ( $record = $result->fetchAssoc () )
        return $record[ 'comments_count' ];

    return 0;
}

function get_user_forum_topic_count ( $uid ) {

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'forum')
        ->propertyCondition('uid', $uid);
    
    $result = $query->execute();
    
    if (isset($result['node']))
        return count($result['node']); 
    
    return 0;
}

function get_user_member_for ( $uid ) {
    $user = user_load($uid);
    return format_interval(REQUEST_TIME - $user->created);
}