<?php
// $Id$

/**
 * @file
 * CRUD functions for Workflow states, transitions and workflow IDs
 */

/**
 * Given a workflow machine name, return the numeric workflow ID
 *
 * Assumes the presence of the patch to add Features compatibility
 * available at http://drupal.org/node/558378
 *
 * @return
 *   numeric workflow ID
 */
function install_workflow_get_wid($machine_name) {
  $wid = db_result(db_query_range("SELECT wid FROM {workflows} WHERE machine_name ='%s'", $machine_name, 0, 1));
  return $wid;
}

/**
 * Get a workflow's transition ID based on the from state and the to states
 *
 * @param $from
 *   The numeric ID of the original state.
 * @param $to
 *   The numeric ID of the transitioning-to state.
 * @return
 *   A numeric transition ID.
 */
function install_workflow_get_transition_id($from, $to) {
  $tid = db_result(db_query("SELECT tid FROM {workflow_transitions} WHERE sid = %d AND target_sid = %d", $from, $to));
  return $tid;
}

/**
 * Get a workflow state ID from its name.
 *
 * @param $state_name
 *   A string containing the state's name
 * @param $module
 *   A string containing the module that uses the state. Defaults to 'workflow'
 * @return
 *   The numeric state ID.
 */
function install_workflow_get_sid($state_name, $module = NULL) {
  if (!isset($module)) {
    $module = 'workflow';
  }
  $sid = db_result(db_query("SELECT sid FROM {workflow_states} WHERE state = '%s' AND module = '%s'", $state_name, $module));
  return $sid;
}
