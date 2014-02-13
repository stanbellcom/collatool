<?php

function collatool_rabbitmq_to_canonical($type, $message){
  switch ($type){
    case 'email':
      return collatool_rabbitmq_to_canonical_email($message);
      break;
    case 'skype':
      return collatool_rabbitmq_to_canonical_skype($message);
      break;
  }
}

function collatool_rabbitmq_to_canonical_email($message){

  $dateTime = new DateTime($message->date);
  $message->date = $dateTime->format('d.m.Y H:i:s');

  return $message;
}

function collatool_rabbitmq_to_canonical_skype($message){

}