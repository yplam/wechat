<?php

/**
 * @file
 * Contains \Drupal\wechat\Controller\WechatController.
 */

namespace Drupal\wechat\Controller;

use Drupal\Core\Controller\ControllerBase;
use Symfony\Component\DependencyInjection\ContainerInterface;
use YPL\WechatSDK\Wechat;

/**
 * Class WechatController.
 *
 * @package Drupal\wechat\Controller
 */
class WechatController extends ControllerBase {

  /**
   * YPL\WechatSDK\Wechat definition.
   *
   * @var YPL\WechatSDK\Wechat
   */
  protected $wechat;
  /**
   * {@inheritdoc}
   */
  public function __construct(Wechat $wechat_default) {
    $this->wechat = $wechat_default;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('wechat.default')
    );
  }

  /**
   * Wechat.
   *
   * @return string
   *   Wechat callback
   */
  public function wechat() {
    return [
        '#type' => 'markup',
        '#markup' => $this->t('Implement method: wechat')
    ];
  }

}
