<?php

/**
 * Create a new book node
 *
 * @param $bookData
 * @return stdClass
 */
function createNewBook ( $bookData ) {

////    example usage
//    $body ="Text for a test body field";
//    $page = array (
//        'title' => 'About' ,
//        'body' => $body ,
//        'uid' => 1 ,
//        'bid' => 'new' ,
//        'format' => 2 ,
//    );

    //set to new book if no parent was set
//    if ( isset( $bookData [ 'path' ] ) ) {
//        $path = array (
//         'alias' => $bookData['path'] ,
//         'pid' => null ,
//         'source' => null ,
//         'language' => LANGUAGE_NONE ,
//         'pathauto' => 1 ,
// {
//     );
//    } else {
//        $path = array (
//            'alias' => '' ,
//            'pid' => null ,
//            'source' => null ,
//            'language' => LANGUAGE_NONE ,
//            'pathauto' => 1 ,
//        );
//    }


    //set to new book if no parent was set
    if ( empty( $bookData [ 'bid' ] ) ) {
        $bookData [ 'bid' ] = 'new';

        $haschildren = 1;
    } else {
        $haschildren = 0;
    }

//    drupal_set_message("book bid - " . $bookData [ 'bid' ]);

    //set current user as default if not set
    if ( ! isset( $bookData [ 'uid' ] ) ) {
        global $user;
        $bookData [ 'uid' ] = $user->uid;
    }


   //make sure right user is being used in drush
    global $user;
    if ( empty ( $bookData[ 'uid' ] ) ) {
        if ( $user->uid == 0 ) {
            $bookData[ 'uid' ] = 1;
        } else {
            $bookData[ 'uid' ] = $user->uid;
        }
    }



    if ( ! isset( $bookData [ 'format' ] ) ) {
        $bookData [ 'format' ] = 'wiki';
    }
    // set 0 weight if none set
    if ( ! isset( $bookData [ 'weight' ] ) ) {
        $bookData [ 'weight' ] = 0;
    }

    //todo use node object here instead with added arrays

    //node object
    $node = new stdClass();
    $node->title = $bookData [ 'title' ];
    $node->language = LANGUAGE_NONE;
    $node->body[ LANGUAGE_NONE ][ 0 ] = array (
        'value' => $bookData [ 'body' ] ,
        'format' => 'wiki' ,
    );
    $node->uid = 1;
//    $node->uid = $bookData [ 'uid' ];

    $node->type = 'book';
    node_object_prepare ( $node );

//    $node->path = $path;
    $node->created = time ();
    $node->promote = 0;
    $node->status = 1;
    $node->format = 'wiki';
//    $node->format = $bookData ['format'];
//    $node->language = 'en';


//    book_node_prepare($node);


//    $node->book = array (
//        'bid' => $bookData [ 'bid' ] , // use 'new' here if the book page is of a new book
//             'bid' => 'new', // use 'new' here if the book page is of a new book
        //     'plid' => $node->book['mlid'],
//        'weight' => $bookData [ 'weight' ] ,
//        'options' => array () ,
//        'module' => 'book',
//        'has_children' => $haschildren,
//    );

    $node->book = array(
     'bid' => $bookData [ 'bid' ], // use 'new' here if the book page is of a new book
//     'plid' => $node->book['mlid'],
     'weight' => $bookData [ 'weight' ],
     'options' => array(),
//     'has_children' => $haschildren,
     'module' => 'book',
     );



    node_save ( $node );

//    drupal_set_message_array($node);

    return $node;


}


/**
 *  Util for creating child book with a known parent bid
 *
 */
function createChildBook ($bookPageData, $parentBook) {
    $bookPageData ['bid'] = $parentBook;
    $book = createNewBook ($bookPageData);
//    drupal_set_message("created child book - " . $parentBook );
    return $book;
}

function loadBookByTitle ( $title ) {
    //todo clean up example
    //    $book = loadBookByTitle ( $aboutPage->title );
    //    $parentBook = $book[ 0 ][ 'bid' ];
    //    drupal_set_message_array($aboutPage, "wowwww");


//    $books = book_get_books ();
    $result = db_query ( "SELECT n.nid FROM {node} n WHERE n.title = :title AND n.type = :type" ,
        array ( ":title" => $title , ":type" => 'book' ) );
    $nid = $result->fetchField ();

    if ( isset( $nid ) ) {

        $query = db_select ( 'book' , 'b' , array ( 'fetch' => PDO::FETCH_ASSOC ) );
        $query->join ( 'node' , 'n' , 'b.nid = n.nid' );
        $query->join ( 'menu_links' , 'ml' , 'b.mlid = ml.mlid' );
        $query->condition ( 'n.nid' , $nid );
        $query->addField ( 'n' , 'nid' , 'nid' );
        $query->addField ( 'n' , 'type' , 'type' );
        $query->addField ( 'n' , 'title' , 'title' );
        $query->addField ( 'n' , 'uid' , 'uid' );
        $query->fields ( 'b' );

        $result2 = $query->execute ();

        foreach ( $result2 as $link ) {
            $all_books[ ] = $link;
        }

//        drupal_set_message_array ( $nid );
        drupal_set_message_array ( $all_books );

        return $all_books;
    } else {

        drupal_set_message_array ( "there is not book by title " . $title );

    }


}

