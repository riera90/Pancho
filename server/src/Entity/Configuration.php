<?php

namespace App\Entity;

use Symfony\Component\Validator\Constraints as Assert;
use Doctrine\ORM\Mapping as ORM;

/**
 * @ORM\Entity(repositoryClass="App\Repository\ConfigurationRepository")
 */
class Configuration
{
    /**
     * @ORM\Id()
     * @ORM\GeneratedValue()
     * @ORM\Column(type="integer")
     */
    private $id;


    /**
     * @ORM\Column(type="string", length=255)
     */
    private $serverName;

    /**
     * @ORM\Column(type="string", length=25)
     * @Assert\Choice(
     *     choices = {"master","slave"},
     *     message = "The allowed values are 'master' or 'slave'",
     * )
     */
    private $serverMode;



    public function getId(): ?int
    {
        return $this->id;
    }

    public function getServerMode(): ?string
    {
        return $this->serverMode;
    }

    public function setServerMode(string $serverMode): self
    {
        $this->serverMode = $serverMode;

        return $this;
    }

    public function getServerName(): ?string
    {
        return $this->serverName;
    }

    public function setServerName(string $serverName): self
    {
        $this->serverName = $serverName;

        return $this;
    }
}
