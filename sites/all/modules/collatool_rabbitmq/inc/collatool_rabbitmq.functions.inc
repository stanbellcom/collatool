<?php

define(DATE_FORMAT, 'd.m.Y H:i:s');

function collatool_rabbitmq_to_canonical($type, $message) {
  switch ($type) {
    case 'email':
      return collatool_rabbitmq_to_canonical_email($message);
      break;
    case 'skype':
      return collatool_rabbitmq_to_canonical_skype($message);
      break;
  }
}

/* Canonical format of message:
 * external_id
 * date (in format dd.mm.yyy HH:mm:ii)
 * sender
 * receiver
 * body
 * meta (used for search and other)
 *
*/
function collatool_rabbitmq_to_canonical_email($message) {
  //id
  $message->external_id = $message->id;

  //change date format
  $dateTime = new DateTime($message->date);
  $message->date = $dateTime->format(DATE_FORMAT);

  //extract meta information
  preg_match_all('/(^\w.+:\n)?(^>.*(\n|$))+/mi', $message->body, $meta);
  $message->meta = collatool_rabbitmq_multi_implode($meta);
  $message->meta = preg_replace('/>*/', '', $message->meta);

  //add subject to meta information
  $message->meta = $message->subject . ' ' . $message->meta;
  unset($message->subject);

  //remove quotated text from body
  $message->body = preg_replace('/(^\w.+:\n)?(^>.*(\n|$))+/mi', '', $message->body);

  //setting source
  $message->source = 'email';

  return $message;
}

function collatool_rabbitmq_to_canonical_skype($message) {
  //id
  $message->external_id = $message->id;

  //change date format
  $message->date = date(DATE_FORMAT, $message->date);

  //strip emotion tags
  $message->body = preg_replace('/<\/?ss(.|\s)*?>/', '', $message->body);

  //setting source
  $message->source = 'skype';

  return $message;
}

function collatool_rabbitmq_multi_implode($array) {
  $return = '';

  foreach ($array as $item) {
    if (is_array($item)) {
      $return .= collatool_rabbitmq_multi_implode($item);
    }
    else {
      $return .= $item;
    }
  }

  return $return;
}