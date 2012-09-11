<?php


/**
 * Save an existing file as a drupal file object
 *
 * @param array $settings
 * @return bool|stdClass
 *
 */

//todo redundant?
//    example usage
//    $settings = array (
//        'path' => '/path/to/file.extension' ,
//        'default_destination' => '/destination/of/file' ,
//        'scheme' => 'public' ,
//    );
//    $file = saveExistingFiletoDrupal($settings);
//    if ($file) {//etc} else {//error}
function saveExistingFiletoDrupal ( array $settings ) {
//    if ( empty($settings['sourceFilePath']) || empty($settings['destinationFilePath'] ) || empty
//    ($settings['filename'] ) ) {
//        return FALSE;
//    }
//    'sourceFilePath' => $sourceImage ,
//    'filePath' => $filePath ,
//    'fileName' => $filename ,
//    'destinationPath' => $destinationPath ,

    //default scheme to public
    if ( ! isset( $settings[ 'scheme' ] ) ) {
        $settings[ 'scheme' ] = 'public';
    }

    //setup the destination stuff
    $destinationDirectory = $settings[ 'scheme' ] . '://' . $settings[ 'destinationPath' ] ;
    file_prepare_directory ( $destinationDirectory , FILE_CREATE_DIRECTORY );

    $destinationFilePath = $destinationDirectory . $settings[ 'fileName' ];
    $file = file_save_data ( file_get_contents ( $settings['filePath'] . $settings['fileName'] ) , $destinationFilePath );

    return $file;
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


function renderImageFileMarkup ( $file , array $settings ) {
    //use the -l with drush eg - drush test -y -l http://haxedev
//    $settings = array (
//        'alt' => 'Haxe Cross Platform Diagram' ,
//        'style' => '100x100' ,
//    );

    //see if there is an image style preset
    if ( empty ( $settings[ 'style' ] ) ) {
        $imagePath = $file->uri;
    } else {
        $imagePath = image_style_path ( $settings[ 'style' ] , $file->uri );
    }

    $featured_image = array (
        'path' => $imagePath ,
        'alt' => $settings[ 'alt' ] ,
    );
    //possible to add more
//        'width' => '500',
//        'height' => '500',
//        'attributes' => array ( 'class' => 'slider_view' ) ,

    //create the image with a link to its view page
    $imageMarkup = theme_image ( $featured_image );

    return $imageMarkup;
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

