<?php

/**
 * Create a new node_content entity based on a settings array
 * Include images id array to attach file fields
 *
 * @param array $settings
 *
 * @return bool
 *
 *
 *
 *  Example
$node = array (
    'title' => 'Home' ,
    'type' => 'site_page' ,
    'bodyformat' => 'markdown' ,
    'path' => 'home',
    'uid' => 1 ,
);
createNode ( $node );
 *
 */
function createNode ( array $settings ) {

    //prepare standard settings
    $node = new stdClass();
    $node->type = $settings[ 'type' ];
    $node->bundle = 'node_content';
    $node->title = $settings[ 'title' ];
    node_object_prepare ( $node );

    //setup more settings
    $node->custom = TRUE;
    $node->modified = TRUE;
    $node->locked = FALSE;
    $node->status = 1;
    $node->active = 1;
    $node->promote = 1;
    
    //todo language specific
    $node->language = LANGUAGE_NONE;
    
    //core body field
    if ( !empty ( $settings[ 'body' ] ) ) {
        if ( empty ( $settings[ 'bodyformat' ] ) ) {
            $settings[ 'bodyformat' ] = 'plain_text';
        }
        $node->body[ LANGUAGE_NONE ][ 0 ] = array (
            'value' => $settings[ 'body' ] ,
            'format' => $settings[ 'bodyformat' ] ,
        );
    }
    
    //pathauto settings
    if ( !empty ( $settings[ 'path' ] ) ) {
        $node->path['pathauto'] = TRUE;
        $node->path['alias'] = $settings[ 'path' ];
        $node->pathauto_perform_alias = TRUE;
    }

    //make sure right user is being used in drush
    global $user;
    if ( empty ( $settings[ 'uid' ] ) ) {
        if ( $user->uid == 0 ) {
            $node->uid = 1;
        } else {
            $node->uid = $user->uid;
        }
    } else {
        $node->uid = $settings[ 'uid' ];
    }

    // Set the timestamp fields.
    if ( !empty( $settings[ 'created' ] ) )
        $node->created = $settings[ 'created' ];

    if ( !empty( $settings[ 'changed' ] ) )
        $node->changed = $settings[ 'changed' ];

    if ( !empty( $settings[ 'timestamp' ] ) )
        $node->timestamp = $settings[ 'timestamp' ];
    
    node_save ( $node );

}
