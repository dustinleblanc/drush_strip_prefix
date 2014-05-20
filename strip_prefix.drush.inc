<?php

/**
 * @file
 *  Drush command to strip table prefixes from a drupal database.
 */

/**
 * Implements hook_drush_command().
 */
function strip_prefix_drush_command() {
  $items = array();
  $items['strip_prefix'] = array(
    'description' => "Finds all tables in a drupal database containing a specific prefix and renames the tables to remove the prefix.",
    'arguments' => array(
      'prefix' => "the prefix we are looking to strip from the database tables."
    ),
    'required-arguments' => TRUE,
    'examples' => array(
      'drush strip @foo parent_' => "Removes the prefix 'parent_' from all tables on the 'foo' site if they exist.",
    ),
    'aliases' => array('strip'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
    'core' => array('7.x'),
  );
  return $items;
}

/**
 * Implements drush_COMMANDFILE_COMMANDNAME().
 */
function drush_strip_prefix(string $prefix) {
  $old_tables = db_query("SHOW TABLES")->fetchCol();
  $context = drush_get_context(DRUSH_DB_CREDENTIALS);
  $db = $context['name'];
  $msg = 'You are about to strip the prefix ' . '\'' . $prefix . '\'' . ' from all database tables in the database ' . '\'' . $db . '\'' . '; Are you sure you want to continue?(this cannot be undone)';
  if(drush_confirm($msg)) {
    foreach($old_tables as $key => $old_table) {
      if (strpos($old_table, $prefix) !== FALSE) {
        $new_table = str_replace($prefix, '', $old_table);
        // first drop $new_table incase it already exists
        $clean_sql = "DROP TABLE IF EXISTS $new_table";
        db_query($clean_sql);
        $rename_sql = "RENAME TABLE $old_table TO $new_table";
        db_query($rename_sql);
        drush_print('Renaming ' . $old_table . ' to ' . $new_table);
      }
    }
  }
  drush_print('Remember to fix the settings file in your drupal installation to point to your new unprefixed database!');
}
