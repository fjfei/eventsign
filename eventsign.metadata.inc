<?php

/**
 * @file
 * Provides Entity metadata integration.
 */

/**
 * Extend the defaults.
 */
class EventsignMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['type'] = array(
      'type' => 'eventsign_type',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer eventsigns',
      'required' => TRUE,
      'description' => eventsign_get_string('type label'),
    ) + $properties['type'];

    $properties['label'] = array(
      'label' => t('Label'),
      'type' => 'text',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'schema field' => 'label',
    );
    $properties['begindate'] = array(
      'label' => t("Begin Date"),
      'type' => 'datetime',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'schema field' => 'begindate',
    );
    $properties['enddate'] = array(
      'label' => t("End Date"),
      'type' => 'datetime',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'schema field' => 'enddate',
    );
    $properties['user'] = array(
      'label' => t("User"),
      'type' => 'user',
      'description' => t("The owner of the @eventsign.", array('@eventsign' => eventsign_get_string('entity label'))),
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_setter_method',
      'setter permission' => 'administer eventsigns',
      'required' => TRUE,
      'schema field' => 'uid',
    );

    $properties['created'] = array(
      'label' => t("Date created"),
      'type' => 'date',
      'description' => t("The date the @eventsign was created.", array('@eventsign' => eventsign_get_string('entity label'))),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer eventsigns',
      'schema field' => 'created',
    );

    $properties['changed'] = array(
      'label' => t("Date changed"),
      'type' => 'date',
      'schema field' => 'changed',
      'description' => t("The date the @eventsign was most recently updated.", array('@eventsign' => eventsign_get_string('entity label'))),
    );

    $properties['status'] = array(
      'label' => t("Status"),
      'type' => 'boolean',
      'schema field' => 'status',
      'description' => t("Whether the @eventsign is active (true) or not (false).", array('@eventsign' => eventsign_get_string('entity label'))),
    );

    return $info;
  }
}
