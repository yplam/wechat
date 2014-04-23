<?php


function wechat_admin_settings(){
  $form['config'] = array(
    '#type' => 'fieldset',
    '#title' => t('WeChat Config'),
	  '#collapsible' => TRUE,
	  '#collapsed' => FALSE,
  );
  $form['config']['config_token'] = array(
    '#type' => 'textfield',
    '#title' => t('WeChat Token'),
    '#description' => t('WeChat Account Token'),
    '#default_value' => variable_get('wechat_config_token', ""),
    '#required' => true,
  );
  $form['config']['config_appid'] = array(
    '#type' => 'textfield',
    '#title' => t('AppID'),
    '#description' => t('Account APPID'),
    '#default_value' => variable_get('wechat_config_appid', ""),
    '#required' => true,
  );
  $form['config']['config_appsecret'] = array(
    '#type' => 'textfield',
    '#title' => t('AppSecret'),
    '#description' => t('Account AppSecret'),
    '#default_value' => variable_get('wechat_config_appsecret', ""),
    '#required' => true,
  );
  $form['config']['submit_config'] = array(
    '#type' => 'submit',
    '#value' => t('save'),
    '#submit' => array('wechat_admin_config_submit'),
  );

  $form['default_message'] = array(
    '#type' => 'fieldset',
    '#title' => t('Auto reply'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['default_message']['default_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Auto reply message'),
    '#description' => t('The WeChat module will send this message to user if no other Modules '),
    '#default_value' => variable_get('wechat_default_message', "hello, I'm wechat"),
    '#required' => true,
  );
  $form['default_message']['follow_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Auto reply message after follow.'),
    '#description' => '',
    '#default_value' => variable_get('wechat_follow_message', "hello, I'm wechat"),
    '#required' => false,
  );
  $form['default_message']['submit_message'] = array(
    '#type' => 'submit',
    '#value' => t('Save Message'),
    '#submit' => array('wechat_admin_default_message_submit'),
  );
  $form['update_menu'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update Wechat Menu'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['update_menu']['submit_menu'] = array(
    '#type' => 'submit',
    '#value' => t('Update Menu'),
    '#submit' => array('wechat_admin_update_menu_submit'),
  );
  return $form;
}

function wechat_admin_config_submit($form, &$form_state){
  variable_set('wechat_config_token', $form_state['values']['config_token']);
  variable_set('wechat_config_appid', $form_state['values']['config_appid']);
  variable_set('wechat_config_appsecret', $form_state['values']['config_appsecret']);

}

function wechat_admin_default_message_submit($form, &$form_state){
  variable_set('wechat_default_message', $form_state['values']['default_message']);
  variable_set('wechat_follow_message', $form_state['values']['follow_message']);
}


function _wechat_menu_item($subval){
  $subelement = array();
  $subelement['name'] = $subval['link']['link_title'];
  if(isset($subval['link']['options']['attributes']['wechat_type'])
      && $subval['link']['options']['attributes']['wechat_type'] == 'click'){
	  $subelement['type'] = 'click';
	  $subelement['key'] = $subval['link']['options']['attributes']['wechat_key'];
  }
  else{
    $subelement['type'] = 'view';
	  $subelement['url'] = $subval['link']['options']['attributes']['wechat_url'];
  }
  return $subelement;
}


function _wechat_menu_arr(){
  $menu_tree = menu_build_tree('wechat', array('max_depth'=>2));
  $menu_arr = array();
  $menu_arr['button'] = array();
  foreach($menu_tree as $val){
    if($val['link']['hidden']){
      continue;
    }
    $element = array();
    $element['name'] = $val['link']['link_title'];
    $element['sub_button'] = array();
    if(!empty($val['below'])){
      foreach($val['below'] as $subval){
        if($subval['link']['hidden']){
          continue;
        }
        $element['sub_button'][] = _wechat_menu_item($subval);
      }
    }
    if(empty($element['sub_button'])){
      unset($element['sub_button']);
      $element = _wechat_menu_item($val);
    }
    $menu_arr['button'][] = $element;
  }
  return $menu_arr;
}


function wechat_admin_update_menu_submit($form, &$form_state){
  $menu_arr = _wechat_menu_arr();
  if(empty($menu_arr['button'])){
    drupal_set_message('Empty WeChat Menu', 'error');
  }
  else{
	  $weObj = _wechat_init_obj();
    if($weObj->createMenu($menu_arr))
  	{
      drupal_set_message('Update menu success.');
  	}
  	else{
  	  drupal_set_message($weObj->errMsg.'-'.$weObj->errCode, 'error');
  	}
  }
  return;
}

