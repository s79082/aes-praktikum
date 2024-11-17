# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.define "alice" do |alice|
    alice.vm.box = "ubuntu/jammy64"
    alice.vm.hostname = "alice"
    alice.vm.network "private_network", ip: "192.168.56.101", virtualbox__intnet: "internal"
    alice.vm.provider "virtualbox" do |vb|
      vb.customize ["modifyvm", :id, "--nicpromisc2", "allow-all"]
      vb.customize ["modifyvm", :id, "--memory", 2048]
    end
    alice.vm.provision "shell", path: "provision_common.sh"
  end

end
