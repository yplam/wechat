<?php

/**
 * @file
 * Contains \Drupal\wechat\WechatCacheAdapterServiceInterface.
 */

namespace Drupal\wechat;

/**
 * Interface WechatCacheAdapterServiceInterface.
 *
 * @package Drupal\wechat
 */
interface WechatCacheAdapterServiceInterface {

    public function get($key);

    public function set($key, $data, $expire);
}
