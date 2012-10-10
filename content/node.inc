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
 *
 * Example Forum topic node
 *
$node = array (
'title' => 'Welcome' ,
'forum' => 'General discussion' ,
'type' => 'forum' ,
'sticky' => 1 ,
'uid' => $user->uid ,
'bodyformat' => 'markdown' ,
'body' => "Welcome to the forum." ,
);
$node = createNode ( $node );
 *
 */
function createNode ( array $settings ) {

    //prepare standard settings
    $node = new stdClass();
    $node->type = $settings[ 'type' ];
    $node->bundle = 'node_content';
    $node->title = $settings[ 'title' ];
    node_object_prepare ( $node );

    //some more of what could be added
    $node->custom = TRUE;
    $node->modified = TRUE;
    $node->locked = FALSE;
    $node->status = 1;
    $node->active = 1;
    $node->promote = 1;
    $node->nid = NULL;

    if ( ! empty ( $settings[ 'sticky' ] ) ) {
        $node->sticky = $settings[ 'sticky' ];

    }

    //todo language specific
    $node->language = LANGUAGE_NONE;

    //pathauto settings
    if ( ! empty ( $settings[ 'path' ] ) ) {
        $node->path[ 'pathauto' ] = TRUE;
        $node->path[ 'alias' ] = $settings[ 'path' ];
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
    if ( ! empty( $settings[ 'created' ] ) )
        $node->created = $settings[ 'created' ];

    if ( ! empty( $settings[ 'changed' ] ) )
        $node->changed = $settings[ 'changed' ];

    if ( ! empty( $settings[ 'timestamp' ] ) )
        $node->timestamp = $settings[ 'timestamp' ];

    //text fields
    if ( ! empty ( $settings[ 'text_fields' ] ) ) {
        $text_fields = $settings[ 'text_fields' ];

        foreach ( $text_fields as $tfield ) {
            $field = $tfield[ 'field_name' ];
            $options = array ();
            $options[ 'und' ][ ] = array (
                'value' => $tfield[ 'text' ] ,
                'format' => NULL ,
            );
            $node->$field = $options;
        }
    }

    //forum topic fields
    if ( ! empty ( $settings[ 'forum' ] ) ) {
        $forumTaxonomy = taxonomy_get_term_by_name ( $settings[ 'forum' ] );
        //the index is the tid, note this does not work with multiple names that are the same
        $first_key = key ( $forumTaxonomy );
        $node->taxonomy_forums[ 'und' ][ 0 ][ 'tid' ] = $forumTaxonomy[ $first_key ]->tid;
    }

    //core body field
    if ( ! empty ( $settings[ 'body' ] ) ) {
        if ( empty ( $settings[ 'bodyformat' ] ) ) {
            $settings[ 'bodyformat' ] = 'plain_text';
        }
        $node->body[ LANGUAGE_NONE ][ 0 ] = array (
            'value' => $settings[ 'body' ] ,
            'format' => $settings[ 'bodyformat' ] ,
        );
    }

    //core body field as description
    if ( ! empty ( $settings[ 'description' ] ) ) {
        if ( empty ( $settings[ 'description_format' ] ) ) {
            $settings[ 'description_format' ] = 'plain_text';
        }
        $node->field_description[ LANGUAGE_NONE ][ 0 ] = array (
            'value' => $settings[ 'description' ] ,
            'format' => $settings[ 'description_format' ] ,
        );
    }

    //helper function for any field you want, just get the syntax right :)
    if ( ! empty ( $settings[ 'fields' ] ) ) {
        $fields = $settings[ 'fields' ];

        foreach ( $fields as $field ) {
            $node->$field[ 'name' ] = $field[ 'options' ];
        }
    }

    node_save_action ( $node );

    //use the correct filefield path if drush uid 0
    global $user;
    if ( ! empty ( $settings[ 'fields' ] ) && ( $user->uid == 0 ) && module_exists('filefield_paths') ) {
        foreach ( $fields as $field ) {
            if ( isset( $field[ 'type' ] ) ) {
                if ( $field[ 'type' ] == 'file' ) {
                    $field_name = $field[ 'name' ];
                    $entity_type = 'node';
                    $bundle_name = $node->type;
                    $info_instance = field_info_instance ( $entity_type , $field_name , $bundle_name );
                    $target_path = $info_instance[ 'settings' ][ 'filefield_paths' ][ 'file_path' ][ 'value' ];
                    $token_data = array ( 'node' => node_load ( $node->nid ) );
                    $target_path = token_replace ( $target_path , $token_data , array ( 'clear' => TRUE ) );
                    $file_field = $node->$field_name;
                    $files = $file_field[ 'und' ];
                    foreach ( $files as $file ) {
                        $file_object = file_load ( $file[ 'fid' ] );
                        $original_filename = $file[ 'filename' ];
                        $target_path = file_default_scheme () . '://' . $target_path . "/";
                        $target_path_basename = $target_path . $original_filename;
                        file_prepare_directory ( $target_path , FILE_CREATE_DIRECTORY , 'file_directory_path' );
                        file_move ( $file_object , $target_path_basename );
                    }
                }
            }
        }
    }
    
    return $node;

}
