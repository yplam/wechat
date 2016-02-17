<?php

/**
 * @file
 * Contains \Drupal\wechat\Tests\WechatController.
 */

namespace Drupal\wechat\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\wechat\WechatService;

/**
 * Provides automated tests for the wechat module.
 */
class WechatControllerTest extends WebTestBase {

  /**
   * Drupal\wechat\WechatService definition.
   *
   * @var Drupal\wechat\WechatService
   */
  protected $wechat_default;
  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => "wechat WechatController's controller functionality",
      'description' => 'Test Unit for module wechat and controller WechatController.',
      'group' => 'Other',
    );
  }

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();
  }

  /**
   * Tests wechat functionality.
   */
  public function testWechatController() {
    // Check that the basic functions of module wechat.
    $this->assertEquals(TRUE, TRUE, 'Test Unit Generated via App Console.');
  }

}
