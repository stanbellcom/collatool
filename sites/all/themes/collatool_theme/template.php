<?php

/**
 * @file
 * template.php
 */

function collatool_theme_node_view_alter(&$build){
    $node = $build['#node'];
    if($node->type == "task")
    {
        $breadcrumb = drupal_get_breadcrumb();

	//find project refering to this task:
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
	->propertyCondition('type', array('project'))
	->fieldCondition('field_pr_tasks', 'target_id', $node->nid, '=');

	$result = $query->execute();
	if (isset($result['node'])){
	    $nids = array_keys($result['node']);
	    $project = node_load($nids[0]);
            $breadcrumb[] = l($project->title, 'node/' . $project->nid);
	}
    
        drupal_set_breadcrumb($breadcrumb);
    }
}