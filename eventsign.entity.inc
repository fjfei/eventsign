<?php

/**
 * @file
 * Holds entity related classes.
 */

/**
 * The eventsign entity controller.
 */
class EventsignController extends EntityAPIController {

  /**
   * Overridden to add in more default values.
   */
  public function create(array $values = array()) {
    $values += array(
      'created' => REQUEST_TIME,
      'langcode' => LANGUAGE_NONE,
    );
    return parent::create($values);
  }
}


/**
 * A eventsign entity.
 */
class EventsignEntity extends Entity {

  public $created;
  public $changed;
  public $id;
  public $type;
  public $begindate;
  public $enddate;
  public $label = '';
  public $status = 1;

  public function __construct($values = array()) {
    // Support creation with the type object also.
    if (isset($values['type']) && is_object($values['type'])) {
      $values['type'] = $values['type']->name;
    }
    parent::__construct($values, 'eventsign');
  }

  /**
   * Overridden to care about created and changed times.
   */
  public function save() {
    // Do not automatically set a created values for already existing entities.
    if (empty($this->created) && (!empty($this->is_new) || !$this->id)) {
      $this->created = REQUEST_TIME;
    }

    $this->changed = REQUEST_TIME;

    parent::save();
  }

  /**
   * Gets the associated eventsign type object.
   *
   * @return EventsignType
   */
  public function type() {
    return eventsign_type_load($this->type);
  }

  /**
   * Implements a custom default URI
   */
  public function defaultUri() {
    return array(
      'path' => eventsign_get_string('base path') . '/' . $this->id,
    );
  }
}

/**
 * A eventsign type entity.
 */
class EventsignType extends Entity {

  public $label = '';
  public $weight = 0;

}