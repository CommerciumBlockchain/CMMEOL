# Commercium CI workers

This folder contains the Ansible playbooks for configuring a fresh OS
installation for use as a Buildbot worker in Commercium's CI.

# Criteria for Adding Workers

a. Don't add workers until users complain about a problem on a platform
   that doesn't yet have workers or if we anticipate many users will use
   a platform, we may pre-emptively add an unsupported worker for it.

b. Prioritize the platforms that seem to have the most users.

c. When adding workers start by adding workers for the "most common"
   variant of any distro, then if users later encounter problems with a
   sub-variant, we can consider adding new workers at that point.
   Example: add Ubuntu Desktop before Xubuntu, on the assumption the
   former has a larger population base.

# Setting up a latent worker on Amazon EC2

- Add a regular (non-latent) worker to the master.cfg for dev-ci.commercium.org, and
  deploy the changes.
  - This enables the Ansible playbook to run to completion, ending in the worker
    connecting to the master.

- Start a basic EC2 instance using the template AMI for the target OS.
  - Choose the smallest instance size, it won't be used for building Commercium.

- Figure out which user to log into the instance with.
  - E.g. for the Ubuntu template, use "ubuntu" instead of "root"
  - If you get an Ansible error later with a message like "Failed to connect to
    the host via ssh: Received message too long 1349281121\r\n", that means the
    instance is sending a text string in response to the SSH connection, and the
    Ansible protocol is balking. Try manually logging in with the same
    credentials to diagnose.

- Create `inventory/hosts` containing the following:

    [commercium-ci-worker-unix]
    some-name ansible_host=<INSTANCE_IP> ansible_ssh_user=<USERNAME>

- Run `ansible-playbook -e buildbot_worker_host_template=templates/host.ec2.j2 -i inventory/hosts unix.yml`,
  passing in the worker's Buildbot name and password.
  - After a successful run, the worker should be connected to dev-ci.commercium.org and
    visible in its worker list.

- Create an AMI from the instance. This is the worker AMI to put into the
  master.cfg for dev-ci.commercium.org.
  - 16 GB of storage should be sufficient.

- SSH into the instance, and edit the worker config to connect to ci.commercium.org.

- Create an AMI from the instance. This is the worker AMI to put into the
  master.cfg for ci.commercium.org.
  - 16 GB of storage should be sufficient.

- Delete the instance (it is no longer needed).

- Edit the master.cfg to turn the new worker into a latent (using the new AMI
  IDs), add it to the appropriate worker groups, set up new builders etc.
  - Deploy this via the normal PR review process.
