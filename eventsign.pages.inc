<?php

/**
 * @file
 * Page callbacks for eventsign module.
 */

/**
 * Eventsign UI controller.
 */
class EventsignUIController extends EntityBundleableUIController {

  /**
   * Provides definitions for implementing hook_menu().
   */
  public function hook_menu() {
    $items = parent::hook_menu();

    // Extend the 'add' path.
    $items[$this->path . '/add']['title'] = 'Add ' . eventsign_get_string('entity label');
    return $items;
  }

  /**
   * Operation form submit callback.
   */
  public function operationFormSubmit($form, &$form_state) {
    parent::operationFormSubmit($form, $form_state);
    $form_state['redirect'] = eventsign_get_string('admin menu path content');
  }
}

/**
 * Generates the eventsign editing form.
 */
function eventsign_form($form, &$form_state, Entity $eventsign, $op = 'edit') {

  // Needed by entity_form_field_validate().
  $form['type'] = array('#type' => 'value', '#value' => $eventsign->type);

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#default_value' => isset($eventsign->label) ? $eventsign->label : '',
    '#description' => t('The label associated with the @eventsign.', array('@eventsign' => eventsign_get_string('entity label'))),
    '#required' => TRUE,
    '#weight' => -15,
  );
  $form['begindate'] = array(
    '#type' => 'textfield',
    '#title' => t('Begin date'),
    '#default_value' => isset($eventsign->begindate) ? format_date($eventsign->begindate, 'short') : '',
    '#description' => t('Event Begin date.'),
    // '#required' => TRUE,
    '#weight' => -14,
  );
  $form['enddate'] = array(
    '#type' => 'textfield',
    '#title' => t('End date'),
    '#default_value' => isset($eventsign->enddate) ? format_date($eventsign->enddate, 'short') : '',
    '#description' => t('Event End date.'),
    // '#required' => TRUE,
    '#weight' => -13,
  );
  $form['created'] = array(
    '#type' => 'textfield',
    '#title' => t('Creation date'),
    '#default_value' => isset($eventsign->created) ? format_date($eventsign->created, 'short') : '',
    '#description' => t('The date when the @eventsign was created.', array('@eventsign' => eventsign_get_string('entity label'))),
    '#required' => TRUE,
    '#weight' => -12,
  );

  $form['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate this @eventsign', array('@eventsign' => eventsign_get_string('entity label'))),
    '#default_value' => !empty($eventsign->status),
    '#weight' => -10,
  );

  field_attach_form('eventsign', $eventsign, $form, $form_state);

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40,
  );

  $form['actions']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#weight' => 45,
    '#limit_validation_errors' => array(),
    '#submit' => array('eventsign_form_submit_delete'),
    '#access' => $op != 'add' && $op != 'clone'
  );

  return $form;
}

/**
 * eventsign editing form validation callback.
 */
function eventsign_form_validate(&$form, &$form_state) {
  entity_form_field_validate('eventsign', $form, $form_state);
}

/**
 * Form API submit callback for the eventsign form.
 */
function eventsign_form_submit(&$form, &$form_state) {
  $date_format = variable_get('date_format_short', 'm/d/Y - H:i');
  $date = date_parse_from_format($date_format, $form_state['values']['created']);
  $begindate = date_parse_from_format($date_format, $form_state['values']['begindate']);
  $enddate = date_parse_from_format($date_format, $form_state['values']['enddate']);
  $form_state['values']['created'] = mktime($date['hour'], $date['minute'], $date['second'], $date['month'], $date['day'], $date['year']);

  $form_state['values']['begindate'] = mktime($begindate['hour'], $begindate['minute'], $begindate['second'], $begindate['month'], $begindate['day'], $begindate['year']);
  $form_state['values']['enddate'] = mktime($enddate['hour'], $enddate['minute'], $enddate['second'], $enddate['month'], $enddate['day'], $enddate['year']);
  $eventsign = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $eventsign->save();
  $form_state['redirect'] = eventsign_get_string('admin menu path content');
}

/**
 * Form API submit callback for the delete button.
 */
function eventsign_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/eventsigns/' . $form_state['eventsign']->id . '/delete';
}