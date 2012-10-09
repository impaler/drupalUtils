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

//returns individual file objects
//$file = new stdClass();
//$file->uri = $uri;
//$file->filename = $filename;
//$file->name = pathinfo($filename, PATHINFO_FILENAME);

function getImagesFromDir ( $imagepath ) {
    $mask = '/[a-zA-Z0-9\_\-\.\]\[]+\.(jpe?g|gif|png|JPE?G|GIF|PNG)$/';
    $ignore = '/(\.\.?|CVS)$/';
    //drupal_set_message ( $imagepath );
    $images = file_scan_directory ( $imagepath , $mask , array ( 'nomask' => $ignore ,
            'callback' => $callback = 0 ,
            'recurse' => $recurse = TRUE ,
            'key' => $key = 'filename' ,
            'min_depth' => $min_depth = 0 )
    );

    return $images;
}

function createFakeFile ($filename, $size_wanted = 126345 ) {
//    $filename    = 'foo.txt'; 
//    $size_wanted =  126345; // bytes 
    $junkdata = NULL; 
    
    while (strlen($junkdata) < $size_wanted) { 
      $junkdata .= chr(mt_rand(32, 126)); 
    } 
    
    $fp = fopen($filename, 'w'); 
    fwrite ($fp, $junkdata); 
    fclose($fp);
}