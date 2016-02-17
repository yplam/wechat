<?php

/**
 * @file
 * Contains \Drupal\wechat\WechatCacheAdapterService.
 */

namespace Drupal\wechat;

use Drupal\Core\Cache\DatabaseBackend;

/**
 * Class WechatCacheAdapterService.
 *
 * @package Drupal\wechat
 */
class WechatCacheAdapterService implements WechatCacheAdapterServiceInterface {

  /**
   * Drupal\Core\Cache\DatabaseBackend definition.
   *
   * @var Drupal\Core\Cache\DatabaseBackend
   */
  protected $cache_default;
  /**
   * Constructor.
   */
  public function __construct(DatabaseBackend $cache_default) {
    $this->cache_default = $cache_default;
  }

  public function get($key) {
    if( $result = $this->cache_default->get($key, false)){
      return $result->data;
    }
    return false;
  }

  public function set($key, $data, $expire) {
    return $this->cache_default->set($key, $data, time()+$expire);
  }

}
