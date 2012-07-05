<?php

class node extends stdClass {
    /**
     * The primary identifier for a node.
     */
    private $nid;

    public function setNid ( int $nid ) {
        $this->nid = $nid;
    }

    public function getNid () {
        return $this->nid;
    }

    /**
     * The current node_revision.vid version identifier.
     */
    private $vid;

    /**
     * The node_type.type of this node.
     */
    private $type;

    /**
      * Boolean indicating whether the node should be displayed at the top of
      * lists in which it appears.
      */
    private $sticky;




    private $title;
    private $uid;

    private $bundle;
    private $language;
    private $custom;
    private $modified;




    public function setBundle ( $bundle ) {
        $this->bundle = $bundle;
    }

    public function getBundle () {
        return $this->bundle;
    }

    public function setCustom ( $custom ) {
        $this->custom = $custom;
    }

    public function getCustom () {
        return $this->custom;
    }

    public function setLanguage ( $language ) {
        $this->language = $language;
    }

    public function getLanguage () {
        return $this->language;
    }

    public function setModified ( $modified ) {
        $this->modified = $modified;
    }

    public function getModified () {
        return $this->modified;
    }

    public function setTitle ( $title ) {
        $this->title = $title;
    }

    public function getTitle () {
        return $this->title;
    }

    public function setType ( $type ) {
        $this->type = $type;
    }

    public function getType () {
        return $this->type;
    }

    public function setUid ( $uid ) {
        $this->uid = $uid;
    }

    public function getUid () {
        return $this->uid;
    }

    public function setVid ( $vid ) {
        $this->vid = $vid;
    }

    public function getVid () {
        return $this->vid;
    }

    public function setSticky ( $sticky ) {
        $this->sticky = $sticky;
    }

    public function getSticky () {
        return $this->sticky;
    }
}






       /**
        * The languages.language of this node.
        */
//       public var language:String;

       /**
        * The title of this node, always treated as non-markup plain text.
        */
//       public var title:String;

       /**
        * The users.uid that owns this node; initially, this is the user that
        * created it.
        */
//       public var uid:Number;

       /**
        * Boolean indicating whether the node is published (visible to
        * non-administrators).
        */
//       public var status:Boolean;

       /**
        * The Unix timestamp when the node was created.
        */
//       public var created:Date;

       /**
        * The Unix timestamp when the node was most recently saved.
        */
//       public var changed:Date;

       /**
        * Whether comments are allowed on this node: 0 = no, 1 = closed (read only),
        * 2 = open (read/write).
        */
//       public var comment:uint;

       /**
        * Boolean indicating whether the node should be displayed on the front page.
        */
//       public var promote:Boolean;





//   $node->nid	Node ID.
//   $node->type	Type of node (e.g. book, page, forum).
//   $node->language	The default language for this node.
//   $node->uid	User ID of node creator.
//   $node->status	unpublished/published (0|1).
//   $node->created	UNIX timestamp of node creation date.
//   $node->changed	UNIX timestamp of last time node was changed.
//   $node->comment	whether comments can be added, read, or accessed, for this node.
//   $node->promote	Promoted to front page (0|1).
//   $node->moderate	Moderation enabled (0|1).
//   $node->sticky	Sticky (0|1).
//   $node->tnid	The node ID of the translation source (or parent, if node is a translation).
//   $node->translate	Is a translation (0|1).
//   $node->vid	The revision ID of the current version of this node.
//   $node->revision_uid	The user ID of the user who created the current revision.
//   $node->title	Page (or, more accurately, node) title.
//   $node->body	Body content of node.
//   $node->teaser	Teaser (the initial part of the body).
//   $node->log	Message left by the creator of this revision, explaining the changes.
//   $node->revision_timestamp	Unix timestamp showing when current revision was created.
//   $node->format	which filter applies to this content.
//   $node->name	Username of node creator.
//   $node->picture	User avatar of the node creator.
//   $node->date	Long date, including timezone data, of when the node was created.
//   $node->revision	TRUE/FALSE this is a new revision (if TRUE, will be saved as a separate entry in the database).
//   $node->menu	Array containing the menu item assigned to the node.
