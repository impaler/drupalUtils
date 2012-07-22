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
    $path =  $_SERVER['DOCUMENT_ROOT'] . base_path() . drupal_get_path('theme', $themeName );
    return $path;
}