<?php

/**
 * Copy a directory recursively.
 *
 * Eg;
drush_op('copy_dir_recursively', $source_dir, $target_dir );
 *
 * */
function copy_dir_recursively ( $source_dir , $target_dir , $ignore = '/^(\.(\.)?|CVS|\.svn|\.git|\.DS_Store)$/' ) {
    if ( ! is_dir ( $source_dir ) ) {
        drush_die ( dt ( 'The directory "!directory" was not found.' , array ( '!directory' => $source_dir ) ) );
    }
    $dir = opendir ( $source_dir );
    @mkdir ( $target_dir );
    while ( $file = readdir ( $dir ) ) {
        if ( ! preg_match ( $ignore , $file ) ) {
            if ( is_dir ( $source_dir . '/' . $file ) ) {
                copy_dir_recursively ( $source_dir . '/' . $file , $target_dir . '/' . $file , $ignore );
            } else {
                copy ( $source_dir . '/' . $file , $target_dir . '/' . $file );
            }
        }
    }
    closedir ( $dir );
}

/**
 * Replace strings in a file.
 *
 * Eg;
$alterations = array(
'text to change' => 'changed text value',
);
drush_op('replace_strings_in_file', $file_path, array_keys($alterations), $alterations);
 *
 *
 */
function replace_strings_in_file ( $file_path , $find , $replace ) {
    $file_contents = file_get_contents ( $file_path );
    $file_contents = str_replace ( $find , $replace , $file_contents );
    file_put_contents ( $file_path , $file_contents );
}

function drupal_get_absolute_theme_path ( $themeName ) {
    //error showing up with drush DOCUMENT_ROOT is not available
    if ( function_exists ( "drush_get_context" ) ) {
        $rootPath = drush_get_context ( 'DRUSH_DRUPAL_ROOT' );
    } else {
        $rootPath = $_SERVER[ 'DOCUMENT_ROOT' ];
    }

    $path = $rootPath . base_path () . drupal_get_path ( 'theme' , $themeName );

    return $path;
}

function createExistingFileFilefieldArray ( $filepath , $fieldName , $uid , $imageOptions = Null ) {

    $file = saveExistingFileToDB ( $filepath , $uid );
    $options = createFileFieldOptions ( $file , $uid , $imageOptions );

    $field = array (
        'name' => $fieldName ,
        'options' => $options ,
    );

    return $field;

}

function createFileFieldOptions ( $file , $userUID , $imageOptions = Null ) {
    $options[ 'und' ][ ] = array (
        'uid' => $userUID ,
        'fid' => $file->fid ,
        'filename' => $file->filename ,
        'uri' => $file->uri ,
        'filemime' => $file->filemime ,
        'filesize' => $file->filesize ,
        'status' => 1 ,
        'display' => 1 ,
    );

    if ( $imageOptions != Null ) {
        $options[ 'und' ][ ] = array (
            'alt' => $imageOptions[ 'alt' ] ,
            'title' => $imageOptions[ 'title' ] ,
        );
    }

    return $options;
}

function createTaxonomyFieldArray ( $fieldName , $tid ) {
    $options[ 'und' ][ ] = array (
        'tid' => $tid ,
    );

    $field = array (
        'name' => $fieldName ,
        'options' => $options ,
    );

    return $field;

}

function createGeshiFieldArray ( $fieldName , $sourcecode , $language ) {

    $options[ 'und' ][ ] = array (
        'sourcecode' => $sourcecode ,
        'language' => $language ,
    );

    $field = array (
        'name' => $fieldName ,
        'options' => $options ,
    );

    return $field;
}

function saveExistingFileToDB ( $filepath , $userUID , $destination = Null ) {
    //save it to the default location if no destination is given
    if ( $destination == Null )
        $destination = file_default_scheme () . '://' . basename ( $filepath );

    $file = file_save_data ( file_get_contents ( $filepath ) , $destination );
    if ( $file == FALSE )
        return FALSE;

    $file = file_load ( $file->fid );
    $file->uid = $userUID;

    $file = file_save ( $file );
    return $file;
}