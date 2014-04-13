<?php

function collatool_analytics_graph_comments_sources($values) {
  $options = new stdClass();
  $options->chart = (object) array(
    'renderTo' => 'container',
    'plotBackgroundColor' => NULL,
    'plotBorderWidth' => NULL,
    'plotShadow' => FALSE,
  );
  $options->title = new StdClass();
  $options->title->text = t('Comment sources');

  $options->tooltip = new StdClass();
  $options->tooltip->formatter = "function() {return '<b>'+ this.point.name + ' (' + this.y + ')</b>: '+ this.percentage +' %';}";

  $options->plotOptions = new StdClass();
  $options->plotOptions->pie = (object) array(
    'allowPointSelect' => TRUE,
    'cursor' => 'pointer',
    'dataLabels' => array(
      'enabled' => TRUE,
    ),
    'showInLegend' => TRUE,
  );

  $options->series = array();
  $series = new StdClass();
  $series->type = 'pie';
  $series->name = 'Slices';
  $series->data = array();
  foreach ($values as $key => $value) {
    $series->data[] = array($key, $value);
  }
  $options->series[] = $series;

  $options->credits = new StdClass();
  $options->credits->enabled = FALSE;

  return highcharts_render($options);
}

function collatool_analytics_graph_comments_user_activity($values) {
  $options = new stdClass();

  $options->chart = (object) array(
    'renderTo' => 'container',
    'plotBackgroundColor' => NULL,
    'plotBorderWidth' => NULL,
    'plotShadow' => FALSE,
  );

  $options->title = new StdClass();
  $options->title->text = t('User Activity');

  $options->tooltip = new StdClass();
  $options->tooltip->formatter = "function() {return '<b>'+ this.point.name +'</b>: '+ this.y;}";

  $options->plotOptions = new StdClass();
  $options->plotOptions->column = (object) array(
    'allowPointSelect' => TRUE,
    'cursor' => 'pointer',
    'dataLabels' => array(
      'enabled' => TRUE,
    ),
    'showInLegend' => FALSE,
  );

  $options->yAxis = new StdClass();
  $options->yAxis->allowDecimals = FALSE;
  $options->yAxis->title = new StdClass();
  $options->yAxis->title->text = t('Number of messages');
  $options->yAxis->labels = new StdClass();
  $options->yAxis->labels->enabled = TRUE;

  $options->series = array();

  foreach ($values as $key => $value) {
    $series = new StdClass();
    $series->type = 'bar';
    $series->name = $key;
    $series->data = array();
    $series->data[] = array($key, $value);
    $options->series[] = $series;
  }

  $options->credits = new StdClass();
  $options->credits->enabled = FALSE;

  return highcharts_render($options);
}

function collatool_analytics_graph_comments_word_count($values) {
  $options = new stdClass();

  $options->chart = (object) array(
    'renderTo' => 'container',
    'plotBackgroundColor' => NULL,
    'plotBorderWidth' => NULL,
    'plotShadow' => FALSE,
  );

  $options->title = new StdClass();
  $options->title->text = t('Word count');

  $options->tooltip = new StdClass();
  $options->tooltip->formatter = "function() {return '<b>'+ this.point.name +'</b>: '+ this.y;}";

  $options->plotOptions = new StdClass();
  $options->plotOptions->column = (object) array(
    'allowPointSelect' => TRUE,
    'cursor' => 'pointer',
    'dataLabels' => array(
      'enabled' => FALSE,
    ),
    'showInLegend' => FALSE,
  );

  $options->yAxis = new StdClass();
  $options->yAxis->title = new StdClass();
  $options->yAxis->title->text = t('Number of words');

  $options->xAxis = new StdClass();
  $options->xAxis->title = new StdClass();
  $options->xAxis->title->text = t('Words');
  $options->xAxis->labels = new StdClass();
  $options->xAxis->labels->enabled = FALSE;

  $options->series = array();
  $series = new StdClass();
  $series->type = 'column';
  $series->name = 'Slices';
  $series->data = array();
  foreach ($values as $key => $value) {
    $series->data[] = array($key, $value);
  }

  $options->series[] = $series;

  $options->credits = new StdClass();
  $options->credits->enabled = FALSE;

  return highcharts_render($options);
}

function collatool_analytics_graph_comments_activity($values) {
  $options = new stdClass();

  $options->chart = (object) array(
    'renderTo' => 'container',
    'plotBackgroundColor' => NULL,
    'plotBorderWidth' => NULL,
    'plotShadow' => FALSE,
  );

  $options->title = new StdClass();
  $options->title->text = t('Activity');

  $options->tooltip = new StdClass();
  $options->tooltip->formatter = "function() {return '<b>Messages</b>: '+ this.y}";

  $options->plotOptions = new StdClass();
  $options->plotOptions->area = (object) array(
    'allowPointSelect' => TRUE,
    'cursor' => 'pointer',
    'dataLabels' => array(
      'enabled' => FALSE,
    ),
    'showInLegend' => TRUE,
  );

  $options->yAxis = new StdClass();
  $options->yAxis->allowDecimals = FALSE;
  $options->yAxis->title = new StdClass();
  $options->yAxis->title->text = t('Number of messages');

  $options->xAxis = new StdClass();
  $options->xAxis->title = new StdClass();
  $options->xAxis->title->text = t('Period');
  $options->xAxis->type = 'datetime';

  $options->series = array();
  foreach ($values as $key => $seria) {
    $series = new StdClass();
    $series->type = 'area';
    $series->name = $key;
    $series->data = array();
    foreach ($seria as $key => $value) {
      $series->data[] = array($key, $value);
    }
    $options->series[] = $series;
  }

  $options->credits = new StdClass();
  $options->credits->enabled = FALSE;

  return highcharts_render($options);
}

function collatool_analytics_graph_comments_daytime_activity($values) {
  $options = new stdClass();

  $options->chart = (object) array(
    'renderTo' => 'container',
    'plotBackgroundColor' => NULL,
    'plotBorderWidth' => NULL,
    'plotShadow' => FALSE,
  );

  $options->title = new StdClass();
  $options->title->text = t('Daytime activity');

  $options->tooltip = new StdClass();
  $options->tooltip->formatter = "function() {return '<b>Messages at ' + this.x + '.00 ' +this.series.name + '</b>: '  + this.y}";

  $options->plotOptions = new StdClass();
  $options->plotOptions->bubble = (object) array(
    'allowPointSelect' => TRUE,
    'cursor' => 'pointer',
    'dataLabels' => array(
      'enabled' => TRUE,
    ),
    'showInLegend' => TRUE,
  );

  $options->yAxis = new StdClass();
  $options->yAxis->allowDecimals = FALSE;
  $options->yAxis->title = new StdClass();
  $options->yAxis->title->text = t('Number of messages');
  $options->yAxis->min = 0;

  $options->xAxis = new StdClass();
  $options->xAxis->title = new StdClass();
  $options->xAxis->title->text = t('Time of the day');
  $options->xAxis->min = 0;
  $options->xAxis->max = 23;

  $options->series = array();
  foreach ($values as $key => $seria) {
    $series = new StdClass();
    $series->name = $key;
    $series->type = 'area';
    $series->data = array();
    for ($i = 0; $i < 23; $i++){
      //$series->data[] = array($i, $seria[$i] ? $seria[$i] : 0);
    }

    foreach ($seria as $key => $value) {
      $series->data[] = array($key, $value);
    }
    $options->series[] = $series;
  }

  $options->credits = new StdClass();
  $options->credits->enabled = FALSE;

  return highcharts_render($options);
}