<?

/**
 * Create a new Taxonomy vocabulary
 *
 * @param $settings
 *
 * @return Status constant indicating whether the vocabulary was inserted (SAVED_NEW) or updated(SAVED_UPDATED).
 *
Eg;

$settings   = array (
'machine_name'              => 'tags' ,
'name'                      => 'Tags' ,
'description'               => 'Multiple tags used to describe the artwork' ,
'nodes'                     => array ( 'artwork_image' ) ,
'multiple'                  => 1 ,
'required'                  => 1 ,
);
create_taxonomy_vocabulary ( $settings );
 *
 *
 */
function create_taxonomy_vocabulary ( array $settings ) {
    $description = t ( $settings[ 'description' ] );

    if ( ! isset( $settings[ 'help' ] ) )
        $help = "";

    $vocabulary = (object) array (
        'name' => t ( $settings[ 'name' ] ) ,
        'description' => $description ,
        'machine_name' => $settings[ 'machine_name' ] ,
        'help' => $help ,
        'nodes' => $settings[ 'nodes' ] ,
        'multiple' => $settings[ 'multiple' ] ,
        'required' => $settings[ 'required' ] ,
    );

    return taxonomy_vocabulary_save ( $vocabulary );
}

/**
 * Create a new Taxonomy Term
 *
 * @param $settings
 *
 * @return bool|int Status constant indicating whether term was inserted (SAVED_NEW) or updated (SAVED_UPDATED)
 *
Eg;

$tag_presets = array (
'Dark' , 'Bright' , 'Cute' , 'Funny' , 'Evil' , 'Atmosphere' , 'Landscape' ,
'Old' , 'Fresh' , 'Colourful' , 'HDR' , 'Nature' , 'Industrial' , 'Modern'
);

for ( $i = 0 ; $i < count ( $tag_presets ) ; $i ++ ) {
$term = array (
'name'                      => $tag_presets[ $i ] ,
'vid'                       => $vocabulary->vid ,
);

create_taxonomy_term ( $term );
}

Or;
$term = array (
'name' => 'Digital Art' ,
//$vocabulary = taxonomy_vocabulary_machine_name_load ( 'vocabulary_machine_name' ] );
'vid' => $vocabulary->vid ,
);
create_taxonomy_term ( $term );
 *
 *
 */
function create_taxonomy_term ( array $settings ) {
    $term = new stdClass();
    $term->name = $settings[ 'name' ];
    $term->vid = $settings[ 'vid' ];
    if ( isset( $settings[ 'weight' ] ) ) $term->weight = $settings[ 'weight' ];
    $term->parent = empty ( $settings[ 'parent' ] ) ? 0 : $settings[ 'parent' ];
    if ( ! empty ( $settings[ 'description' ] ) ) $term->description = $settings[ 'description' ];

    return taxonomy_term_save ( $term );
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
