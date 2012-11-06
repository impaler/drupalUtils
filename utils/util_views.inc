<?

function render_view ( $name , $display_id = 'default', $args=null ) {

    $view = views_get_view ( $name );
    
    if ( $view ) {
        if ($args != null)
        $view->set_arguments($args);
        $view->hide_admin_links = TRUE;
        if ( ! $view || ! $view->access ( $display_id ) ) {
            return null;
        }
        $output =  $view->preview ( $display_id );
        if ($view->result) {
             return $output;
        } else {
            return null;
        }
        
    } else {
        
        drupal_set_message ('the view ' . $display_id . ' does not exist', 'error');
        
        return FALSE;
    }

}
