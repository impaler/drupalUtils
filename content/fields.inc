<?

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


//todo media tokens etc

function createMediaTokenFileFromPath ( $path ) {
    //save file in path to dest
    
    //return createImagetoken
}

function createMediaImagetoken ( $fid ) {
//function createMediaImagetoken ( $fid, array $attributes = null ) {
        
    
    
//    [[{"type":"media","view_mode":"media_large","fid":"5","attributes":{"alt":"","class":"custom-name","height":"300","width":"400"}}]]
    
//    [[{"type":"media","view_mode":"media_large","fid":"1","attributes":{}}]]
    
//    $fid = 2;
    
    $opentag = '[[{';
    $closetag = '}]]';
    $commar = ',';
    
    $fid_tag = '"fid":';
    
    $view_modetag = '"view_mode":';
    $view_mode = "media_large";

    $typetag = '"type":';
    $type = '"media"';
    
    $token = "";
    $token = $opentag;
    $token .= $typetag . $type . $commar;
    $token .= $view_modetag . $view_mode. $commar;
    $token .= $fid_tag . '"' . $fid . '"' . $commar;
    $token .= '"attributes":{}';
    $token .= $closetag;
    
    
    
//    $token .= '[[{"type":'.$type.', "view_mode":'.$view_mode.',"fid":"'.$fid.'"'.'}]]';
    
    
//    $entity_info['file']['view modes']['media_link'] = array('label' => t('Link'), 'custom settings' => TRUE);
//    $entity_info['file']['view modes']['media_preview'] = array('label' => t('Preview'), 'custom settings' => TRUE);
//    $entity_info['file']['view modes']['media_small'] = array('label' => t('Small'), 'custom settings' => TRUE);
//    $entity_info['file']['view modes']['media_large'] = array('label' => t('Large'), 'custom settings' => TRUE);
//    $entity_info['file']['view modes']['media_original'] = array('label' => t('Original'), 'custom settings' => TRUE);
    

    
    
    return $token;
}