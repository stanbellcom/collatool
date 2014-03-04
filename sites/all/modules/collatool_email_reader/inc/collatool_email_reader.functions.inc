<?php

function collatool_email_reader_get_message_general_info($inbox, $email_number) {
  $overview = imap_fetch_overview($inbox, $email_number, 0);
  $subject = imap_utf8($overview[0]->subject);
  $sender = imap_utf8($overview[0]->from);
  $receiver = imap_utf8($overview[0]->to);
  $date = $overview[0]->date;
  $uid = $overview[0]->uid;

  $message = array(
    'id' => $uid,
    'date' => $date,
    'sender' => $sender,
    'receiver' => $receiver,
    'subject' => $subject,
  );

  return $message;
}

function collatool_email_reader_get_message_body($inbox, $email_number) {
  $structure = imap_fetchstructure($inbox, $email_number);

  if ($structure->subtype == 'PLAIN') {
    $message = utf8_encode($data = imap_fetchbody($inbox, $email_number, 1, FT_PEEK));
    return $message;
  }
  else {
    $flattenedParts = collatool_email_reader_flatten_parts($structure->parts);
    foreach ($flattenedParts as $partNumber => $part) {
      switch ($part->type) {
        case 0:
          // the HTML or plain text part of the email
          $message = utf8_encode(collatool_email_reader_get_part($inbox, $email_number, $partNumber, $part->encoding));
          return $message;
          // now do something with the message, e.g. render it
          break;
        default:
          break;
//      For future improvements
//      case 1: // multi-part headers, can ignore
//        break;
//      case 2: // attached message headers, can ignore
//        break;
//      case 3: // application
//      case 4: // audio
//      case 5: // image
//      case 6: // video
//      case 7: // other
//        $filename = collatool_email_reader_get_filename_from_part($part);
//        if ($filename) {
//          // it's an attachment
//          $attachment = collatool_email_reader_get_part($inbox, $email_number, $partNumber, $part->encoding);
//          // now do something with the attachment, e.g. save it somewhere
//        }
//        else {
//          // don't know what it is
//        }
//        break;
      }
    }
  }
}

function collatool_email_reader_flatten_parts($messageParts, $flattenedParts = array(), $prefix = '', $index = 1, $fullPrefix = TRUE) {
  foreach ($messageParts as $part) {
    $flattenedParts[$prefix . $index] = $part;
    if (isset($part->parts)) {
      if ($part->type == 2) {
        $flattenedParts = collatool_email_reader_flatten_parts($part->parts, $flattenedParts, $prefix . $index . '.', 0, FALSE);
      }
      elseif ($fullPrefix) {
        $flattenedParts = collatool_email_reader_flatten_parts($part->parts, $flattenedParts, $prefix . $index . '.');
      }
      else {
        $flattenedParts = collatool_email_reader_flatten_parts($part->parts, $flattenedParts, $prefix);
      }
      unset($flattenedParts[$prefix . $index]->parts);
    }
    $index++;
  }

  return $flattenedParts;
}

function collatool_email_reader_get_part($connection, $messageNumber, $partNumber, $encoding) {
  $data = imap_fetchbody($connection, $messageNumber, $partNumber, FT_PEEK);
  switch ($encoding) {
    case 0:
      return $data; // 7BIT
    case 1:
      return $data; // 8BIT
    case 2:
      return $data; // BINARY
    case 3:
      return base64_decode($data); // BASE64
    case 4:
      return quoted_printable_decode($data); // QUOTED_PRINTABLE
    case 5:
      return $data; // OTHER
  }
}

//function collatool_email_reader_get_filename_from_part($part) {
//  $filename = '';
//  if ($part->ifdparameters) {
//    foreach ($part->dparameters as $object) {
//      if (strtolower($object->attribute) == 'filename') {
//        $filename = $object->value;
//      }
//    }
//  }
//
//  if (!$filename && $part->ifparameters) {
//    foreach ($part->parameters as $object) {
//      if (strtolower($object->attribute) == 'name') {
//        $filename = $object->value;
//      }
//    }
//  }
//
//  return $filename;
//}
 