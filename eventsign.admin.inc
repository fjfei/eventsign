<?php

/**
 * @file
 * Admin page callbacks for the eventsign module.
 */

/**
 * UI controller.
 */
class EventsignTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = eventsign_get_string('admin menu description');
    return $items;
  }
}

/**
 * Menu callback; presents main checkin page.
 */
function eventsign_main_page() {
  $build['content']['#markup'] = 'It works!';
//  $build['#attached']['js'][] = drupal_get_path('module', 'eventsign') . '/eventsign.js';
  return $build;
}


/**
 * Generates the eventsign type editing form.
 */
function eventsign_type_form($form, &$form_state, Entity $eventsign_type, $op = 'edit') {

  if ($op == 'clone') {
    $eventsign_type->label .= ' (cloned)';
    $eventsign_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $eventsign_type->label,
    '#description' => t('The human-readable name of this @eventsign-type.', array('@eventsign-type' => eventsign_get_string('type label'))),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($eventsign_type->name) ? $eventsign_type->name : '',
    '#maxlength' => 32,
    '#disabled' => $eventsign_type->hasStatus(ENTITY_IN_CODE) && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'eventsign_type_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this @eventsign-type. It must only contain lowercase letters, numbers, and underscores.', array('@eventsign-type' => eventsign_get_string('type label'))),
  );
  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#default_value' => $eventsign_type->weight,
    '#description' => t('When showing @eventsign, those with lighter (smaller) weights get listed before @eventsign with heavier (larger) weights.', array('@eventsign' => eventsign_get_string('entity plural label'))),
    '#weight' => 10,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save @eventsign-type', array('@eventsign-type' => eventsign_get_string('type label'))),
    '#weight' => 40,
  );
  $form['actions']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete @eventsign-type', array('@eventsign-type' => eventsign_get_string('type label'))),
    '#weight' => 45,
    '#limit_validation_errors' => array(),
    '#submit' => array('eventsign_type_form_submit_delete'),
    '#access' => !$eventsign_type->hasStatus(ENTITY_IN_CODE) && $op != 'add' && $op != 'clone'
  );
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function eventsign_type_form_submit(&$form, &$form_state) {
  $eventsign_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $eventsign_type->save();
  $form_state['redirect'] = eventsign_get_string('admin menu path');
}

/**
 * Form API submit callback for the delete button.
 */
function eventsign_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = eventsign_get_string('admin menu path') . '/' . $form_state['eventsign_type']->name . '/delete';
}